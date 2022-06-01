#include "table.h"

Table::Table() {

	hPen = CreatePen(PS_NULL, 0, 0);
	lf = { 0 };

	WCHAR fontName[LF_FACESIZE] = L"Arial";
	memcpy(lf.lfFaceName, fontName, LF_FACESIZE);
	lf.lfWeight = 1000;

	if (T_SIZE > 3)
	{
		lf.lfHeight = TEXT_HEIGHT_2048;
		mapText["title"] = { L"2048", CreateFontIndirect(&lf), RGB(119, 110, 101), STANDART_BG_COLOR };
	}

	lf.lfHeight = TEXT_HEIGHT_SCORE;
	mapText["score"] = { L"score", CreateFontIndirect(&lf), RGB(238, 228, 218), TABLE_COLOR };
	mapText["best"] = { L"best", CreateFontIndirect(&lf), RGB(238, 228, 218), CELL_COLOR };

	lf.lfHeight = HEIGHT_SCORE;
	mapText["points"] = { L"", CreateFontIndirect(&lf), RGB(255, 255, 255), TABLE_COLOR };

	mapBrush["table"] = CreateSolidBrush(TABLE_COLOR);
	mapBrush["cell"] = CreateSolidBrush(CELL_COLOR);
	mapBrush["mainTable"] = CreateSolidBrush(MAIN_TABLE_COLOR);
}

Table::~Table() {
	DeleteObject(hPen);
	for (auto obj : mapBrush)
		DeleteObject(obj.second);
	for (auto obj : mapText)
		DeleteObject(obj.second.font);
}

void Table::UpdateTabel() {

	mapBrush["table"] = CreateSolidBrush(TABLE_COLOR);
	mapBrush["cell"] = CreateSolidBrush(CELL_COLOR);
	mapBrush["mainTable"] = CreateSolidBrush(MAIN_TABLE_COLOR);

	if (T_SIZE > 3)
	{
		lf.lfHeight = TEXT_HEIGHT_2048;
		mapText["title"].font = CreateFontIndirect(&lf);
		mapText["title"].colorBG = STANDART_BG_COLOR;
	}

	lf.lfHeight = TEXT_HEIGHT_SCORE;

	mapText["score"].font = CreateFontIndirect(&lf);
	mapText["score"].colorBG = TABLE_COLOR;

	mapText["best"].font = CreateFontIndirect(&lf);
	mapText["best"].colorBG = TABLE_COLOR;

	lf.lfHeight = HEIGHT_SCORE;
	mapText["points"].font = CreateFontIndirect(&lf);
	mapText["points"].colorBG = TABLE_COLOR;
}


void Table::draw(HDC hDc, POINT pos, POINT posCell[M_TS][M_TS], INT score, INT best) {

	HPEN hOldPen = (HPEN)SelectObject(hDc, hPen);

	printText(hDc, pos, "title");

	pos.y += MULTIPLIER;
	printLabel(hDc, pos.x + TABLE_SIZE_PIXELS - LABEL_SIZE.x - BORDER_SIZE * 2, pos.y, "score", score);
	printLabel(hDc, pos.x + TABLE_SIZE_PIXELS, pos.y, "best", best);

	pos.y += MULTIPLIER * 9;
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDc, mapBrush["mainTable"]);
	RoundRect(hDc, pos.x, pos.y, pos.x + TABLE_SIZE_PIXELS, pos.y + TABLE_SIZE_PIXELS, ROUND_SIZE, ROUND_SIZE);

	SelectObject(hDc, mapBrush["cell"]);
	for (int i = 0; i < T_SIZE; i++)
		for (int j = 0; j < T_SIZE; j++)
		{
			RoundRect(hDc, posCell[i][j].x + 1, posCell[i][j].y + 1, 
				posCell[i][j].x + CELL_SIZE - 1, posCell[i][j].y + CELL_SIZE - 1,
				ROUND_SIZE, ROUND_SIZE);
		}

	SelectObject(hDc, hOldBrush);
	SelectObject(hDc, hOldPen);
}


void Table::printText(HDC hDc, POINT pos, std::string type, std::wstring str) {

	HFONT hOldFont = (HFONT)SelectObject(hDc, mapText[type].font);

	SetBkColor(hDc, mapText[type].colorBG);
	SetTextColor(hDc, mapText[type].colorText);

	if (str.size())
		TextOut(hDc, pos.x, pos.y, str.c_str(), str.size());
	else
		TextOut(hDc, pos.x, pos.y, mapText[type].str.c_str(), mapText[type].str.size());

	SelectObject(hDc, hOldFont);
}


void Table::printLabel(HDC hDc, INT sx, INT sy, std::string type, INT s) {
	SIZE sz;
	std::wostringstream oss;
	oss << s;
	std::wstring scores(oss.str());

	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDc, mapBrush["table"]);
	RoundRect(hDc, sx - LABEL_SIZE.x, sy, sx, sy + LABEL_SIZE.y, ROUND_SIZE, ROUND_SIZE);

	HFONT hOldFont = (HFONT)SelectObject(hDc, mapText[type].font);
	GetTextExtentPoint32(hDc, mapText[type].str.c_str(), mapText[type].str.size(), &sz);
	printText(hDc, { sx - LABEL_SIZE.x / 2 - sz.cx / 2, sy + MULTIPLIER }, type);

	SelectObject(hDc, mapText["points"].font);
	GetTextExtentPoint32(hDc, scores.c_str(), scores.size(), &sz);
	printText(hDc, { sx - LABEL_SIZE.x / 2 - sz.cx / 2, sy + (long)MULTIPLIER * 5 / 2 }, "points", scores);

	SelectObject(hDc, hOldBrush);
	SelectObject(hDc, hOldFont);
}