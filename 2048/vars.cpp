#include "vars.h"

int T_SIZE = 4;
int MULTIPLIER = 8;					//15 10 8 4

int CELL_SIZE = MULTIPLIER * 10;
int BORDER_SIZE = (int)CELL_SIZE / 10;
int TABLE_SIZE_PIXELS = T_SIZE * (CELL_SIZE + BORDER_SIZE) + BORDER_SIZE;
int ROUND_SIZE = (int)CELL_SIZE / 5;
POINT LABEL_SIZE = { 12 * MULTIPLIER, 12 * MULTIPLIER / 2 };

int TEXT_HEIGHT_2 = (int)64 * MULTIPLIER / 10;			//64
int TEXT_HEIGHT_3 = (int)64 * MULTIPLIER / 10 * 0.8125;	//52
int TEXT_HEIGHT_4 = (int)64 * MULTIPLIER / 10 * 0.625;	//40
int TEXT_HEIGHT_5 = (int)64 * MULTIPLIER / 10 * 0.5;	//32
int TEXT_HEIGHT_2048 = (int)MULTIPLIER * 8.6;			//86
int TEXT_HEIGHT_SCORE = (int)MULTIPLIER * 1.6;			//16
int HEIGHT_SCORE = MULTIPLIER * 3;						//30

COLORREF STANDART_BG_COLOR = RGB(250, 248, 239);
COLORREF TABLE_COLOR = RGB(187, 173, 160);
COLORREF MAIN_TABLE_COLOR = RGB(187, 173, 160);

COLORREF CELL_COLOR = RGB(205, 193, 180);

COLORREF COLOR_2 = RGB(238, 228, 218);
COLORREF COLOR_4 = RGB(237, 224, 200);
COLORREF COLOR_8 = RGB(242, 177, 121);
COLORREF COLOR_16 = RGB(245, 149, 99);

COLORREF COLOR_32 = RGB(246, 124, 95);
COLORREF COLOR_64 = RGB(246, 94, 59);
COLORREF COLOR_128 = RGB(237, 207, 114);
COLORREF COLOR_256 = RGB(237, 204, 97);

COLORREF COLOR_512 = RGB(237, 200, 80);
COLORREF COLOR_1024 = RGB(237, 197, 63);
COLORREF COLOR_2048 = RGB(237, 194, 46);
COLORREF COLOR_4096 = RGB(237, 184, 44);

COLORREF COLOR_8192 = RGB(237, 174, 42);
COLORREF COLOR_16384 = RGB(237, 164, 40);
COLORREF COLOR_32768 = RGB(237, 154, 38);
COLORREF COLOR_65536 = RGB(237, 144, 36);

COLORREF TEXT_COLOR_BLACK = RGB(119, 110, 101);
COLORREF TEXT_COLOR_WHITE = RGB(249, 246, 242);

std::map<INT, Font> fonts =
{
	{ 2,{ TEXT_COLOR_BLACK, COLOR_2, TEXT_HEIGHT_2} },
	{ 4,{ TEXT_COLOR_BLACK, COLOR_4, TEXT_HEIGHT_2 } },
	{ 8,{ TEXT_COLOR_WHITE, COLOR_8, TEXT_HEIGHT_2 } },
	{ 16,{ TEXT_COLOR_WHITE, COLOR_16, TEXT_HEIGHT_2 } },
	{ 32,{ TEXT_COLOR_WHITE, COLOR_32, TEXT_HEIGHT_2 } },
	{ 64,{ TEXT_COLOR_WHITE, COLOR_64, TEXT_HEIGHT_2 } },
	{ 128,{ TEXT_COLOR_WHITE, COLOR_128, TEXT_HEIGHT_3 } },
	{ 256,{ TEXT_COLOR_WHITE, COLOR_256, TEXT_HEIGHT_3 } },
	{ 512,{ TEXT_COLOR_WHITE, COLOR_512, TEXT_HEIGHT_3 } },
	{ 1024,{ TEXT_COLOR_WHITE, COLOR_1024, TEXT_HEIGHT_4 } },
	{ 2048,{ TEXT_COLOR_WHITE, COLOR_2048, TEXT_HEIGHT_4 } },
	{ 4096,{ TEXT_COLOR_WHITE, COLOR_4096, TEXT_HEIGHT_4 } },
	{ 8192,{ TEXT_COLOR_WHITE, COLOR_8192, TEXT_HEIGHT_4 } },
	{ 16384,{ TEXT_COLOR_WHITE, COLOR_16384, TEXT_HEIGHT_5 } },
	{ 32768,{ TEXT_COLOR_WHITE, COLOR_32768, TEXT_HEIGHT_5 } },
	{ 65536,{ TEXT_COLOR_WHITE, COLOR_65536, TEXT_HEIGHT_5 } },
};

void CalculateConsts(int new_table_size, int new_multiplier_size) {

	T_SIZE = new_table_size;
	MULTIPLIER = new_multiplier_size;					//15 10 8 4 

	CELL_SIZE = MULTIPLIER * 10;
	BORDER_SIZE = (int)CELL_SIZE / 10;
	TABLE_SIZE_PIXELS = T_SIZE * (CELL_SIZE + BORDER_SIZE) + BORDER_SIZE;
	ROUND_SIZE = (int)CELL_SIZE / 5;
	LABEL_SIZE = { 12 * MULTIPLIER, 12 * MULTIPLIER / 2 };

	TEXT_HEIGHT_2 = (int)64 * MULTIPLIER / 10;			//64
	TEXT_HEIGHT_3 = (int)64 * MULTIPLIER / 10 * 0.8125;	//52
	TEXT_HEIGHT_4 = (int)64 * MULTIPLIER / 10 * 0.625;	//40
	TEXT_HEIGHT_5 = (int)64 * MULTIPLIER / 10 * 0.5;	//32
	TEXT_HEIGHT_2048 = (int)MULTIPLIER * 8.6;			//86
	TEXT_HEIGHT_SCORE = (int)MULTIPLIER * 1.6;			//16
	HEIGHT_SCORE = MULTIPLIER * 3;						//30

	fonts[2].size = TEXT_HEIGHT_2;
	fonts[4].size = TEXT_HEIGHT_2;
	fonts[8].size = TEXT_HEIGHT_2;
	fonts[16].size = TEXT_HEIGHT_2;
	fonts[32].size = TEXT_HEIGHT_2;
	fonts[64].size = TEXT_HEIGHT_2;

	fonts[128].size = TEXT_HEIGHT_3;
	fonts[256].size = TEXT_HEIGHT_3;
	fonts[512].size = TEXT_HEIGHT_3;

	fonts[1024].size = TEXT_HEIGHT_4;
	fonts[2048].size = TEXT_HEIGHT_4;
	fonts[4096].size = TEXT_HEIGHT_4;
	fonts[8192].size = TEXT_HEIGHT_4;

	fonts[16384].size = TEXT_HEIGHT_5;
	fonts[32768].size = TEXT_HEIGHT_5;
	fonts[65536].size = TEXT_HEIGHT_5;
}

void ChangeColors(int themeNumber) {
	switch (themeNumber)
	{
	case 1: 
	{
		STANDART_BG_COLOR = RGB(250, 248, 239);

		MAIN_TABLE_COLOR = RGB(187, 173, 160);
		TABLE_COLOR = RGB(187, 173, 160);
		CELL_COLOR = RGB(205, 193, 180);

		COLOR_2 = RGB(238, 228, 218);
		fonts[2].colorBackground = COLOR_2;
		fonts[2].colorText = TEXT_COLOR_BLACK;

		COLOR_4 = RGB(237, 224, 200);
		fonts[4].colorBackground = COLOR_4;
		fonts[4].colorText = TEXT_COLOR_BLACK;

		COLOR_8 = RGB(242, 177, 121);
		fonts[8].colorBackground = COLOR_8;
		fonts[8].colorText = TEXT_COLOR_WHITE;

		COLOR_16 = RGB(245, 149, 99);
		fonts[16].colorBackground = COLOR_16;
		fonts[16].colorText = TEXT_COLOR_WHITE;


		COLOR_32 = RGB(246, 124, 95);
		fonts[32].colorBackground = COLOR_32;
		fonts[32].colorText = TEXT_COLOR_WHITE;

		COLOR_64 = RGB(246, 94, 59);
		fonts[64].colorBackground = COLOR_64;
		fonts[64].colorText = TEXT_COLOR_WHITE;

		COLOR_128 = RGB(237, 207, 114);
		fonts[128].colorBackground = COLOR_128;
		fonts[128].colorText = TEXT_COLOR_WHITE;

		COLOR_256 = RGB(237, 204, 97);
		fonts[256].colorBackground = COLOR_256;
		fonts[256].colorText = TEXT_COLOR_WHITE;

		COLOR_512 = RGB(237, 200, 80);
		fonts[512].colorBackground = COLOR_512;
		fonts[512].colorText = TEXT_COLOR_WHITE;

		COLOR_1024 = RGB(237, 197, 63);
		fonts[1024].colorBackground = COLOR_1024;
		fonts[1024].colorText = TEXT_COLOR_WHITE;

		COLOR_2048 = RGB(237, 194, 46);
		fonts[2048].colorBackground = COLOR_2048;
		fonts[2048].colorText = TEXT_COLOR_WHITE;

		break;
	}
	case 2: {

		STANDART_BG_COLOR = RGB(250, 250, 250);

		MAIN_TABLE_COLOR = RGB(175, 196, 165);
		TABLE_COLOR = RGB(39, 171, 46);
		CELL_COLOR = RGB(216, 242, 203);

		COLOR_2 = RGB(250, 250, 250);
		fonts[2].colorBackground = COLOR_2;
		fonts[2].colorText = TEXT_COLOR_BLACK;

		COLOR_4 = RGB(220, 220, 220);
		fonts[4].colorBackground = COLOR_4;
		fonts[4].colorText = TEXT_COLOR_BLACK;

		COLOR_8 = RGB(39, 171, 46);
		fonts[8].colorBackground = COLOR_8;
		fonts[8].colorText = TEXT_COLOR_WHITE;

		COLOR_16 = RGB(222, 207, 75);
		fonts[16].colorBackground = COLOR_16;
		fonts[16].colorText = TEXT_COLOR_WHITE;


		COLOR_32 = RGB(209, 104, 33);
		fonts[32].colorBackground = COLOR_32;
		fonts[32].colorText = TEXT_COLOR_WHITE;

		COLOR_64 = RGB(201, 55, 14);
		fonts[64].colorBackground = COLOR_64;
		fonts[64].colorText = TEXT_COLOR_WHITE;

		COLOR_128 = RGB(143, 30, 13);
		fonts[128].colorBackground = COLOR_128;
		fonts[128].colorText = TEXT_COLOR_WHITE;

		COLOR_256 = RGB(45, 235, 86);
		fonts[256].colorBackground = COLOR_256;
		fonts[256].colorText = TEXT_COLOR_WHITE;

		COLOR_512 = RGB(162, 93, 201);
		fonts[512].colorBackground = COLOR_512;
		fonts[512].colorText = TEXT_COLOR_WHITE;

		COLOR_1024 = RGB(58, 224, 197);
		fonts[1024].colorBackground = COLOR_1024;
		fonts[1024].colorText = TEXT_COLOR_WHITE;

		COLOR_2048 = RGB(242, 255, 0);
		fonts[2048].colorBackground = COLOR_2048;
		fonts[2048].colorText = TEXT_COLOR_WHITE;

		break;
	}
	case 3: {

		STANDART_BG_COLOR = RGB(250, 250, 250);

		MAIN_TABLE_COLOR = RGB(174, 194, 209);
		TABLE_COLOR = RGB(53, 139, 196);
		CELL_COLOR = RGB(135, 179, 212);

		COLOR_2 = RGB(250, 250, 250);
		fonts[2].colorBackground = COLOR_2;
		fonts[2].colorText = TEXT_COLOR_BLACK;

		COLOR_4 = RGB(220, 220, 220);
		fonts[4].colorBackground = COLOR_4;
		fonts[4].colorText = TEXT_COLOR_BLACK;

		COLOR_8 = RGB(66, 161, 235);
		fonts[8].colorBackground = COLOR_8;
		fonts[8].colorText = TEXT_COLOR_WHITE;

		COLOR_16 = RGB(0, 0, 200);
		fonts[16].colorBackground = COLOR_16;
		fonts[16].colorText = TEXT_COLOR_WHITE;


		COLOR_32 = RGB(225, 136, 235);
		fonts[32].colorBackground = COLOR_32;
		fonts[32].colorText = TEXT_COLOR_WHITE;

		COLOR_64 = RGB(255, 0, 145);
		fonts[64].colorBackground = COLOR_64;
		fonts[64].colorText = TEXT_COLOR_WHITE;

		COLOR_128 = RGB(255, 43, 0);
		fonts[128].colorBackground = COLOR_128;
		fonts[128].colorText = TEXT_COLOR_WHITE;

		COLOR_256 = RGB(191, 0, 255);
		fonts[256].colorBackground = COLOR_256;
		fonts[256].colorText = TEXT_COLOR_WHITE;

		COLOR_512 = RGB(162, 93, 201);
		fonts[512].colorBackground = COLOR_512;
		fonts[512].colorText = TEXT_COLOR_WHITE;

		COLOR_1024 = RGB(58, 224, 197);
		fonts[1024].colorBackground = COLOR_1024;
		fonts[1024].colorText = TEXT_COLOR_WHITE;

		COLOR_2048 = RGB(242, 255, 0);
		fonts[2048].colorBackground = COLOR_2048;
		fonts[2048].colorText = TEXT_COLOR_WHITE;

		break;
	}
	default:
		break;
	}
}