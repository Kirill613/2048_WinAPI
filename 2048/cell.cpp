#include "cell.h"



Cell::Cell() {
    lf = { 0 };

    WCHAR fontName[LF_FACESIZE] = L"Arial";
    memcpy(lf.lfFaceName, fontName, LF_FACESIZE);
    lf.lfWeight = 1000;

    hPen = CreatePen(PS_NULL, 0, 0);

    setCellValue(2);
    pos = { 0, 0 };
}

Cell::~Cell() {
    DeleteObject(hmapBrush);
    DeleteObject(hFont);
    DeleteObject(hPen);
}

void Cell::setCellValue(INT value) {
    cellValue = value;   

    std::wostringstream oss;
    oss << cellValue;
    text = oss.str();
}

void Cell::refreshCellSettings() {
    lf.lfHeight = fonts[cellValue].size;

    if (!hFont)
        DeleteObject(hFont);
    hFont = CreateFontIndirect(&lf);

    if (!hmapBrush)
        DeleteObject(hmapBrush);
    hmapBrush = CreateSolidBrush(fonts[cellValue].colorBackground);
}

void Cell::draw(HDC hDC) {
    if (visible) {  

        refreshCellSettings();

        HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
        HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
        HBRUSH hmapBrushOld = (HBRUSH)SelectObject(hDC, hmapBrush);

        SetBkColor(hDC, fonts[cellValue].colorBackground);
        SetTextColor(hDC, fonts[cellValue].colorText);

        RoundRect(hDC, pos.x, pos.y, pos.x + CELL_SIZE, pos.y + CELL_SIZE, ROUND_SIZE, ROUND_SIZE);
        RECT rect = { 
            pos.x, 
            pos.y, 
            pos.x + CELL_SIZE, 
            pos.y + CELL_SIZE 
        };
        DrawText(hDC, text.c_str(), text.size(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        SelectObject(hDC, hOldPen);
        SelectObject(hDC, hOldFont);
        SelectObject(hDC, hmapBrushOld);
    }
}