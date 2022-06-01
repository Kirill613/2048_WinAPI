#pragma once
#include "vars.h"
#include "conf.h"
#include "table.h"
#include "cell.h"
#include <vector>

class Game {
public:
	Game(HWND hWnd, int table_size, int mult);
	~Game();

	struct Move
	{
		BOOLEAN up = false;
		BOOLEAN down = false;
		BOOLEAN left = false;
		BOOLEAN right = false;

		operator bool()
		{
			return (up || down || left || right);
		}

		inline void setFalse()
		{
			up = down = left = right = false;
		}
	} move;

	struct Save
	{
		INT cellValue;
		BOOLEAN vis;
	};

	struct CellPos {
		INT i;
		INT j;
		INT value;
	};

	void LoadTable(int tableSize);
	void SaveTable(int tableSize);

	void draw(HDC hdc, POINT pos);
	void updateColors();
	void calcPos(POINT pos, bool newGame);
	CellPos genCell();
	void key(INT type);
	bool action(bool isNeedGenerate);
	void newGame();

private:
	HWND hwnd;
	INT score;
	INT best;
	Table table;
	Cell cell[M_TS][M_TS];
	POINT posCell[M_TS][M_TS];
	BOOLEAN start = TRUE;
	RECT rectScore;
	INT accessUp = 0;
	BOOLEAN accessGen = true;
	INT tableSize;

	int WINCONDITION;
	int winHappened;



	// �������� si,sj - ���������� di,dj
	bool step(INT si, INT sj, INT di, INT dj);
	void calcScore(INT s);
	void invalidRect(INT i, INT j);
	void checkMove();
	void checkEnd();

	std::string ChooseFile(int size);
};