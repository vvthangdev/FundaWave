///khai bao cac thu vien can thiet
#include <graphics.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <vector>

#define WIDTH 1000
#define HEIGHT 600
#define WINDOW_SIZE 512
#define MAX_AMPLITUDE 32767
//khai bao bien global
extern int SampleNumber;
extern float timeLength;
extern int Fs;
extern char ch;
//Vi tri 2 con tro chuot mau xanh va do
extern int xRedCursor;
extern int xBlueCursor;
//Toa do fx, fy va gia tri cua tan so am f_val
extern std::vector<int> fx;
extern std::vector<int> fy;
extern std::vector<int> f_val;

//Khai bao struct header file wav
typedef struct header {
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short int audio_format;
    short int num_channels;
    int sample_rate;
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;
} header;
//Dat ten moi cho con tro kieu struct header*
typedef struct header* headerP;
void borderRadius();
void theFrameOfTheSoundWave();
void theFrameOfTheCurrentSoundWave();
void theFrameOfTheAutoCorr();
void theFrameOfFrequencyVariation();
////Ve song tren toan bo truc thoi gian
void drawWaveForm(int16_t *data, int num_samples, int color, int startX, int startY, int widthOfWindow, int firstSignal);
//ve song trong cua so dang xet
void drawWavesInTheCurrentWindow(int16_t *data, int num_samples, int color, int startX, int startY, int start);
//tinh toan va ve ham tu tuong quan
void calculateAndDrawAutocorrelation(int16_t *data, float autoCorr, int start, int color, int startX, int startY);
//Chuc nang hien thi max va min ham tu tuong quan
void showMaxMinAutoCorr(float maxAutoCorr, float minAutoCorr);
//Reset cua so
void clearTheWindowFrame(int left, int top, int right, int bottom);
//Xoa do thi song cu va ve lai do thi song hien tai
void drawAndClearCurrentWindow (int16_t *data, int num_samples, int color, int startX, int startY);
//Di chuyen 2 con tro mau xanh va do
void moveTwoCursors(int16_t *data);
//xem gia tri cua tan so dang tro den
void showFrequencyValue(int16_t* data);
//Zoom doan song dang xet
void zoomTheSelectedWave(int16_t *data,int xRedCursor,int xBlueCursor);