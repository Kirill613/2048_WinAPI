#pragma once
#include "conf.h"
#include "vars.h"

class Table
{
public:
	Table();
	~Table();
	void draw(HDC hdc, POINT pos, POINT posCell[M_TS][M_TS], INT scores, INT record);
	void UpdateTabel();
private:
	HPEN hPen;
	LOGFONTW lf;
	std::map<std::string, COLORREF> mapColors;
	std::map<std::string, HBRUSH> mapBrush;

	void printText(HDC hdc, POINT pos, std::string type, std::wstring str = L"");
	void printLabel(HDC hdc, INT sx, INT sy, std::string type, INT scores);

	struct Text {
		std::wstring str;
		HFONT font;
		COLORREF colorText;
		COLORREF colorBG;
	};
	std::map<std::string, Text> mapText;
};