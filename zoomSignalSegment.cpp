#include "funcPrototypes.h"
#include <vector>

//Khai bao bien giu toa do cua con tro mau do va mau xanh
int xRedCursor = 200;
int xBlueCursor = 250;
char ch;
//khai bao 3 vecto co vai tro luu lai toa do cua tan so, gia tri cua tan so
std::vector<int> fx;
std::vector<int> fy;
std::vector<int> f_val;

//Zoom doan song dang tro den khi nhan phim i
void zoomTheSelectedWave(int16_t *data,int xRedCursor,int xBlueCursor) {
	float sample_spacing = (float)(900)/SampleNumber;
	int redCursorIndex, blueCursorIndex;
	redCursorIndex = static_cast<float>(xRedCursor - 50)/sample_spacing;
	blueCursorIndex = static_cast<float>(xBlueCursor - 50)/sample_spacing;
	int num_samples = blueCursorIndex - redCursorIndex;
	drawWaveForm(data, num_samples, LIGHTGREEN, 50, 300, 420, redCursorIndex);
}

void showFrequencyValue(int16_t* data){
	int f_index(0);
	int *bufferf = (int*)malloc(imagesize(50, 420, 950, 580));
	getimage(50, 420, 950, 580, bufferf);
	while (1) {
		if (kbhit()) {
				
			ch = getch();
			if ((ch == ',') && (f_index > 0)) {
				--f_index;
			}
			else if ((ch == '.') && (f_index < fx.size()-1)) {
				++f_index;
			}
			else if (ch == 'z'){
				moveTwoCursors(data);
			}
			else if (ch == 'x' || fx.size() == 0 ) return;
			//dat lai nen
			putimage(50, 420,bufferf, COPY_PUT);
			setcolor (YELLOW);
			//danh dau diem dang xet
			circle(fx[f_index], fy[f_index], 5);
			setcolor(BLACK);
			char buffer[20] = {};
			char buffer2[5] = {};
			strcat(buffer, "f");
			sprintf(buffer2, "%d", f_index+1);
			strcat(buffer, buffer2);
			strcat(buffer, " = ");
			sprintf(buffer2, "%.1d", f_val[f_index]);
			strcat(buffer, buffer2);
			strcat(buffer, " Hz");
			outtextxy(50, 420, buffer);
		}
	}
}

void moveTwoCursors(int16_t* data){
	int *bufferWave = (int*)malloc(imagesize(20, 20, 950, 180));
	getimage(50, 20, 950, 180, bufferWave);
    while (1) {
    	//neu con nhap ky tu thi thuc hien cac thao tac
        if (kbhit()) {
            ch = getch();
            
            if ((ch == 'T') && (xBlueCursor > xRedCursor)) {
                --xBlueCursor;
            }
			else if ((ch == 't') && (xRedCursor>50)) {
            	--xRedCursor;
			}
			else if ((ch == 'P') && (xBlueCursor<950)) {
				++xBlueCursor;
			}
			else if ((ch == 'p') && (xBlueCursor > xRedCursor)) {
				++xRedCursor;			
		 	}
		 	else if (ch == 'f') {
		 		showFrequencyValue(data);
			}
			// Neu nhap phim x se thoat chuc nang hien tai
			else if (ch == 'x') {
				return;
			}
			//Reset 2 duong line
			putimage(50,20,bufferWave, COPY_PUT);
			//Ve 2 duong line moi
			setcolor(RED);
			line(xRedCursor, 180, xRedCursor,20);
			setcolor(BLUE);
			line(xBlueCursor, 180, xBlueCursor,20);
			//Zoom
			if(ch == 'i') {
				clearTheWindowFrame(50, 220, 471, 379);
				theFrameOfTheCurrentSoundWave();
				zoomTheSelectedWave(data, xRedCursor, xBlueCursor);
			}
		}
	}
}