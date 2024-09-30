#include "funcPrototypes.h"

//Ve song tren toan bo truc thoi gian
void drawWaveForm(int16_t *data, int num_samples, int color, int startX, int startY, int widthOfWindow, int firstSignal) {
	float sample_spacing = (float)(widthOfWindow)/num_samples;
    for ( int i = 0; i < num_samples ; i++) {
        int x1 = startX + i * sample_spacing;
        int y1 = startY - (data[i+firstSignal] * 80 / MAX_AMPLITUDE);
        int x2 = startX + (i + 1) * sample_spacing;
        int y2 = startY - (data[i + firstSignal + 1] * 80 / MAX_AMPLITUDE); 

        setcolor(color);
        line(x1, y1, x2, y2);
    }
}

//ve song trong cua so dang xet
void drawWavesInTheCurrentWindow(int16_t *data, int num_samples, int color, int startX, int startY, int start){
	
	float sample_spacing = (float)(420)/WINDOW_SIZE;
	for (int i = 0; i < WINDOW_SIZE ; i++) {
	int x1 = startX + i * sample_spacing;
    int y1 = startY - data[start+i] * 80 / MAX_AMPLITUDE;
    int x2 = startX + (i + 1) * sample_spacing;
    int y2 = startY - data[start + i + 1] * 80 / MAX_AMPLITUDE ; 

	setcolor(color);
	line(x1, y1, x2, y2);
	}
	theFrameOfTheCurrentSoundWave();
}

void drawAGraphOfFrequencyVariation(int &index,int start) {
	float sample_spacing = (float)(900)/SampleNumber;
	int x = 50 + (start + index)*sample_spacing;
	// ve hinh tron bieu dien tan so
	int f0 = (Fs)/index;
	int y = 580 - static_cast<float>(f0-80)/320*160;
	if ( f0 < 400 && f0 > 80 ) {
		fx.push_back(x);
		fy.push_back(y);
		f_val.push_back(f0);
		circle(x , y, 3);
	}
}

void showMaxMinAutoCorr(float maxAutoCorr, float minAutoCorr) {
	setcolor(LIGHTGREEN);
	settextstyle(SMALL_FONT, HORIZ_DIR, 5);
	
	char buffer[50] = {}, rightBuffer[15] = {};
	strcat(buffer, "Max = ");
	sprintf(rightBuffer, "%.1f", maxAutoCorr);
	strcat(buffer, rightBuffer);
	strcat(buffer, ", Min = ");
	sprintf(rightBuffer, "%.1f", minAutoCorr);
	strcat(buffer, rightBuffer);
	outtextxy(550, 220, buffer);
}

void calculateAndDrawAutocorrelation(int16_t *data, float *autoCorr, int start, int color, int startX, int startY) {
	//calculate Autocorrelation
	float sample_spacing = (float)(420)/WINDOW_SIZE*2;
	memset(autoCorr, 0, sizeof(float) * WINDOW_SIZE);
	int final = WINDOW_SIZE/2 +1;
	for (int delay = 0; delay < final ; delay++) {
		for (int i = start; i < start + WINDOW_SIZE - delay; i++) {
			autoCorr[delay] += data[i] * data[i+delay];
		}
	}
	//Gia tri thap nhat xet tu vi tri thu 39 vi tan so toi da la 400Hz
	float maxAutoCorr = 0;
	float minAutoCorr = autoCorr[10];
	int index(10);
	//tan so giong noi cua nu trong khoang 120-400, cua nam la 80-250
	//searchWindow tim trong khoang 133 mau (WindowSize/3.84)
	const int searchWindow = WINDOW_SIZE/3.84;
	for (int i = 10; i < searchWindow; i++) {
	    if (autoCorr[i] > maxAutoCorr) {
	    	index = i;
	        maxAutoCorr = autoCorr[i];
		}
		if(autoCorr[i] < minAutoCorr) {
			minAutoCorr = autoCorr[i];
		}
	}
	setbkcolor(BLACK);
	showMaxMinAutoCorr(maxAutoCorr, minAutoCorr);
	setbkcolor(LIGHTGRAY);
	//Draw the red line in the maximum position closest to the origin of the function R(k)
	int x = index * sample_spacing + startX;
    setcolor(RED);
	line (x , 221, x, 379);
	maxAutoCorr = fabs(autoCorr[0]);
	for ( int i = 0; i < WINDOW_SIZE/2 ; i++) {
        int x1 = startX + i * sample_spacing;
        int y1 = startY - (autoCorr[i]/ maxAutoCorr)* 80;
        int x2 = startX + (i + 1) * sample_spacing;
        int y2 = startY - (autoCorr[i+1]/ maxAutoCorr)* 80; 
        setcolor(color);
        line(x1, y1, x2, y2);
    }
    theFrameOfTheAutoCorr();
    setcolor(LIGHTGREEN);
    drawAGraphOfFrequencyVariation(index,start);
    
}

// Ve khung cua so chi den doan song dang xet
void drawCurentWindowFrame(int start, int num_samples, int *bufferWave) {
	float sample_spacing = (float)(900)/num_samples;
	int left, right;
	left = 50 + start*sample_spacing;
	right = 50 + (start + WINDOW_SIZE) * sample_spacing;
	
	// xoa khung cua so cu
	putimage(50,20,bufferWave, COPY_PUT);
	
	//ve khung cua so moi
	setcolor(WHITE);
	line(left, 180, left, 20);
	line(right, 180, right, 20);
}
//Reset cua so
void clearTheWindowFrame(int left, int top, int right, int bottom){
	setfillstyle(SOLID_FILL, BLACK);
    bar(left, top, right, bottom);
}
//Xoa do thi song cu va ve lai do thi song hien tai
void drawAndClearCurrentWindow (int16_t *data, int num_samples, int color, int startX, int startY) {
    float autoCorr[WINDOW_SIZE];
    int start;
    float sample_spacing = (float)(900)/SampleNumber;
    //Luu hinh anh toan bo song am thanh
    int *bufferWave = (int*)malloc(imagesize(50, 20, 950, 180));
	getimage(50, 20, 950, 180, bufferWave);
	
	int final = num_samples - WINDOW_SIZE/2 +1;
	int step = WINDOW_SIZE/2;
    for(start = 0; start < final; start += step) {
    clearTheWindowFrame(50, 220, 471, 379);
    clearTheWindowFrame(530, 220, 951, 379);
    drawWavesInTheCurrentWindow(data, num_samples, color, 50, 300, start);
    calculateAndDrawAutocorrelation(data, autoCorr, start, color, 530, 300);
    drawCurentWindowFrame(start, num_samples, bufferWave);

	if (kbhit()) {
 		ch = getch();
 		xRedCursor = 50 + (start)*sample_spacing;
		xBlueCursor = xRedCursor + 2*step*sample_spacing;
 		//nhan phim tab se chuyen sang chuc nang zoom
 		if(ch == 'z') {
 		moveTwoCursors(data);
		}
		//nhan phim f de chuyen sang chuc nang xem gia tri tan so
		if(ch == 'f') {
			showFrequencyValue(data);
		}
	}
    delay(300);
	}
	free(bufferWave);
}