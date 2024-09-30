#include "funcPrototypes.h"

//Ve khung vien
void borderRadius() {
	
	theFrameOfTheSoundWave();
	theFrameOfFrequencyVariation();
	setfillstyle(SOLID_FILL, DARKGRAY);
	//left, top, right, bottom
	//theFrameOfTheSoundWave()
	bar(45, 16, 50, 185);
    bar(46, 15, 955, 20);
    //theFrameOfTheCurrentSoundWave()
    bar(45, 216, 50, 385);
    bar(46, 215, 475, 220);
    //theFrameOfTheAutoCorr()
    bar(525, 216, 530, 385);
    bar(526, 215, 955, 220);
    //theFrameOfFrequencyVariation()
    bar(45, 415, 50, 585);
    bar(45, 415, 955, 420);
    
    setfillstyle(SOLID_FILL, WHITE);
    //theFrameOfTheSoundWave()
    bar(950, 20, 955, 185);
    bar(50, 180, 955, 185);
    //theFrameOfTheCurrentSoundWave()
    bar(470, 220, 475, 385);
    bar(50, 380, 475, 385);
    //theFrameOfTheAutoCorr()
	bar(950, 220, 955, 385);
    bar(530, 380, 955, 385);
    //theFrameOfFrequencyVariation()
    bar(950, 420, 955, 585);
    bar(50, 580, 955, 585);
}

//Ve truc toa do cua do thi tan so
void theFrameOfFrequencyVariation() {
	setcolor(YELLOW);
	setlinestyle(DOTTED_LINE, 0, 1);
	settextstyle(SMALL_FONT, HORIZ_DIR, 5);
	for (int i = 150; i < 950; i += 100) {
		line(i, 580, i, 420);
	}
	for (int j = 460; j < 581; j += 40) {
		line(50, j, 950, j);
	}
	setcolor(BLACK);
	char buffer[15];
	float time = (timeLength*1000);
	for (int i = 0; i < 9; i++) {
    	float time1 = static_cast<int>(time/11*i);
		sprintf(buffer, "%.1f", time1);
		outtextxy(i*100+40, 585, buffer);
	}
	int f = 80;
	for (int j = 0; j < 121; j += 40) {
    	
		sprintf(buffer, "%d", f);
		outtextxy(20, 580-j-5 , buffer);
		f += 80;
	}
	char Hz[] = " Hz";
	sprintf(buffer, "%d", 400);
	strcat(buffer, Hz);
	outtextxy(10, 410, buffer);
	
	char milisecond[] = " ms";
	sprintf(buffer, "%d", (int)time);
	strcat(buffer, milisecond);
	outtextxy(950, 585, buffer);
	setlinestyle(SOLID_LINE, 1, 1);
}

//Ve truc toa do cua toan bo song
void theFrameOfTheSoundWave(){
	setcolor(YELLOW);
	setlinestyle(DOTTED_LINE, 0, 1);
	settextstyle(SMALL_FONT, HORIZ_DIR, 5);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	
    bar(0, 0, 50, 1000);
    bar(0, 0, 1500, 20);
    bar(950, 0, 1500, 1000);
    bar(50, 580, 1500, 1000);
    bar(50, 180, 1500, 220);
    bar(50, 380, 1500, 420);
    bar(470, 180, 530, 400);
    // Ve duong net dut
    for (int i = 150; i < 950; i += 100) {
    	line(i, 180, i, 20);
	}
	for (int j = 60; j < 181; j += 40) {
    	line(50, j, 950, j);
	}
	//Cai lai line ve duong net lien
	setlinestyle(SOLID_LINE, 1, 1);
	
	setcolor(BLACK);
	char buffer[15];
	float time = (timeLength*1000);
	for (int i = 1; i < 9; i++) {
    	float time1 = static_cast<int>(time/11*i);
		sprintf(buffer, "%.1f", time1);
		outtextxy(i*100+40, 185, buffer);
	}
	
	char milisecond[] = " ms";
	sprintf(buffer, "%d", (int)time);
	strcat(buffer, milisecond);
	outtextxy(955, 100, buffer);
	outtextxy(10, 20, "32767");
	outtextxy(10, 170, "-32767");
	outtextxy(30, 90, "0");
}

//Ve truc toa do cua song dang tro den
void theFrameOfTheCurrentSoundWave() {
	setcolor(YELLOW);
	for (int x = 150; x < 451; x += 100) {
		setlinestyle(DOTTED_LINE, 0, 1);
    	line(x, 380, x, 220);
	}
	for (int y = 260; y < 341; y +=40){
		line(50, y, 470, y);
	}
	//Cai lai line ve duong net lien
	setlinestyle(SOLID_LINE, 1, 1);
}

void theFrameOfTheAutoCorr() {
	setcolor(YELLOW);
	for (int x = 630; x < 950; x += 100) {
		setlinestyle(DOTTED_LINE, 0, 1);
    	line(x, 380, x, 220);
	}
	for (int y = 260; y < 341; y +=40){
		line(530, y, 950, y);
	}
	setcolor(BLACK);
	char buffer[15];
	char K_Val[] = "K = ";
	sprintf(buffer, "%d", (int)WINDOW_SIZE/2);
	strcat(K_Val, buffer);
	outtextxy(955, 300, K_Val);
	//Cai lai line ve duong net lien
	setlinestyle(SOLID_LINE, 1, 1);
}