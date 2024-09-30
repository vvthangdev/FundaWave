#include "funcPrototypes.h"
#include <vector>

//Bien toan cuc luu gia tri so mau, thoi gian file va tan so lau mau
int SampleNumber;
float timeLength;
int Fs;

int main(int argc, char *argv[]) {
	
	//Định dạng kích thước cho cửa sổ đồ họa
	int width = WIDTH+9;
    int height = HEIGHT+13;
    initwindow(width, height, "Funda_Wave");
    setcolor(LIGHTGRAY);
    setbkcolor(LIGHTGRAY);
    
	//Khai bao con tro file de mo va doc file
	FILE* infile;
	// Khai bao cau truc OPENFILENAME de su dung hop thoai mo file
	OPENFILENAME ofn;
	// Mang de luu duong dan va ten file duoc chon
	char szFile[260];
	// Dat tat ca cac byte trong cau truc OPENFILENAME thanh 0
	ZeroMemory(&ofn, sizeof(ofn));
	// Dat kich thuoc cua cau truc OPENFILENAME
	ofn.lStructSize = sizeof(ofn);
	// Xac dinh cua so chu cua hop thoai mo file (NULL nghia la khong co cua so chu)
	ofn.hwndOwner = NULL;
	// Chi dinh buffer de luu duong dan va ten file
	ofn.lpstrFile = szFile;
	// Dat ky tu dau tien cua duong dan va ten file la null de dam bao chuoi ket thuc
	ofn.lpstrFile[0] = '\0';
	// Dat so ky tu toi da co the luu trong buffer
	ofn.nMaxFile = sizeof(szFile);
	// Dat bo loc cho hop thoai mo file, o day la WAV Files va tat ca cac tep
	ofn.lpstrFilter = "WAV Files (*.wav)\0*.wav\0All Files (*.*)\0*.*\0";
	// Dat chi so cua bo loc duoc chon mac dinh
	ofn.nFilterIndex = 1;
	// Khai bao con tro de luu ten file duoc chon (khong duoc su dung trong truong hop nay)
	ofn.lpstrFileTitle = NULL;
	// Dat so ky tu toi da cho ten file duoc chon (khong duoc su dung trong truong hop nay)
	ofn.nMaxFileTitle = 0;
	// Dat thu muc mac dinh khi mo hop thoai (NULL nghia la khong co thu muc mac dinh)
	ofn.lpstrInitialDir = NULL;
	// Thiet lap cac co cho hop thoai mo file (OFN_PATHMUSTEXIST: duong dan phai ton tai, OFN_FILEMUSTEXIST: file phai ton tai)
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE) {
        // Mở tập tin đã chọn
        infile = fopen(ofn.lpstrFile, "rb");
        if (infile == NULL) {
        	perror("Error opening file");
        	exit(1);
        }
    }
    else {
        // Thong bao nguoi dung da huy viec chon tap tin
        printf("Nguoi dung da huy.\n");
        exit(1);
    }
    
    headerP meta;
    meta = (headerP)malloc(sizeof(header));
    // Doc 36 byte dau tien trong phan Header
	fread(meta, 1, 36, infile);
	
    // Read the remaining portion of Subchunk 1, if its size exceeds 16 bytes.
    if (meta->subchunk1_size > 16) {
        fseek(infile, meta->subchunk1_size - 16, SEEK_CUR);
    }

    // Read Subchunk2ID and Subchunk2Size
    fread(&meta->subchunk2_id, 1, 4, infile);
    fread(&meta->subchunk2_size, 1, 4, infile);
    
    // Read the header
	// do bits_per_sample = 16 (2 byte)
	SampleNumber = meta -> subchunk2_size/2;
	
	Fs = meta -> sample_rate;
	float Ts = 1.0/(float)Fs;
    
    int16_t* inbuff16;
    inbuff16 = (int16_t*)malloc(2 * sizeof(int16_t) * SampleNumber);
    fread(inbuff16, 2, SampleNumber, infile);
    
 	// file length
	timeLength = static_cast<float>(SampleNumber)/Fs;
	//Ve vien
	borderRadius();
	drawWaveForm(inbuff16, SampleNumber, LIGHTGREEN, 50, 100, 900, 0);
	drawAndClearCurrentWindow (inbuff16, SampleNumber, LIGHTGREEN, 200, 300);
	//Vao chuc nang zoom bang cach nhan phim z
	ch = getch();
	if (ch == 'z') {
		moveTwoCursors(inbuff16);
	}
	//xem thong so tan so bang cach nhan phim f
	else if (ch == 'f') {
		showFrequencyValue(inbuff16);
	}
	//giai phong bo nho va dong file
	closegraph();
	free(inbuff16);
	free(meta);
	fclose(infile);    
    return 0;
}
