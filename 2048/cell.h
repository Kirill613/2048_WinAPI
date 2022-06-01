#pragma once
#include "conf.h"
#include "vars.h"

class Cell {
public:
    Cell();
    ~Cell();

    BOOLEAN visible = FALSE;
    BOOLEAN a�cess = TRUE;
    POINT pos;


    void setCellValue(INT value);
    void refreshCellSettings();
    void draw(HDC hdc);

    operator INT() { return cellValue; };

private:
    INT cellValue;
    std::wstring text;

    HFONT hFont;
    HBRUSH hmapBrush;
    HPEN hPen;
    LOGFONTW lf;
};