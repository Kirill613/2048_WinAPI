#pragma once
#include <windows.h>
#include <map>
#include <string>

extern int T_SIZE;
extern int MULTIPLIER;				//15 10 8 4

extern int CELL_SIZE;
extern int BORDER_SIZE;
extern int TABLE_SIZE_PIXELS;
extern int ROUND_SIZE;
extern POINT LABEL_SIZE;

extern int TEXT_HEIGHT_2;
extern int TEXT_HEIGHT_3;
extern int TEXT_HEIGHT_4;
extern int TEXT_HEIGHT_5;
extern int TEXT_HEIGHT_2048;
extern int TEXT_HEIGHT_SCORE;
extern int HEIGHT_SCORE;

extern COLORREF STANDART_BG_COLOR;
extern COLORREF MAIN_TABLE_COLOR;
extern COLORREF TABLE_COLOR;
extern COLORREF CELL_COLOR;

extern COLORREF COLOR_2;
extern COLORREF COLOR_4;
extern COLORREF COLOR_8;
extern COLORREF COLOR_16;

extern COLORREF COLOR_32;
extern COLORREF COLOR_64;
extern COLORREF COLOR_128;
extern COLORREF COLOR_256;

extern COLORREF COLOR_512;
extern COLORREF COLOR_1024;
extern COLORREF COLOR_2048;
extern COLORREF COLOR_4096;

extern COLORREF COLOR_8192;
extern COLORREF COLOR_16384;
extern COLORREF COLOR_32768;
extern COLORREF COLOR_65536;

extern struct Font {
    COLORREF colorText;
    COLORREF colorBackground;
    INT size;
};

extern std::map<INT, Font> fonts;

void CalculateConsts(int new_table_size, int new_multiplier_size);
void ChangeColors(int themeNumber);