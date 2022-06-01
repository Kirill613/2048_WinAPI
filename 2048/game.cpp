#include <vector>
#include <fstream>
#include "game.h"
#include <iostream>

#define checkbit(i, j) (accessUp & (1 << ((i)*T_SIZE+(j))))
#define setbit(i, j) (accessUp |= (1 << ((i)*T_SIZE+(j))))


Game::Game(HWND hWnd, int table_size, int mult) {
	hwnd = hWnd;
	best = 0;
	score = 0;
	WINCONDITION = 2048;
	if (table_size == 3) {
		WINCONDITION = 64;
	}

	winHappened = 0;
	tableSize = table_size;
	CalculateConsts(table_size, mult);
	LoadTable(table_size);
	table = Table();
}

Game::~Game() {
	SaveTable(tableSize);
}
std::string Game::ChooseFile(int size) {
	std::string filename = "";
	switch (size)
	{
	case 3:
		filename = "save3.dat";
		break;
	case 4:
		filename = "save4.dat";
		break;
	case 5:
		filename = "save5.dat";
		break;
	case 6:
		filename = "save6.dat";
		break;
	default:
		break;
	}
	return filename;
}

void Game::LoadTable(int tableSize) {

	std::ifstream file(ChooseFile(tableSize));

	if (file.is_open()) {
		file.read((char*)&best, sizeof(best));
		file.read((char*)&score, sizeof(score));
		file.read((char*)&winHappened, sizeof(winHappened));
		Save temp[M_TS][M_TS];
		file.read((char*)&temp, sizeof(temp));
		for (int i = 0; i < tableSize; i++) {
			for (int j = 0; j < tableSize; j++) {
				cell[i][j].setCellValue(temp[i][j].cellValue);
				cell[i][j].visible = temp[i][j].vis;
			}
		}
		start = false;
		file.close();
	}
}

void Game::SaveTable(int tableSize) {

	std::ofstream file(ChooseFile(tableSize));

	if (file.is_open()) {
		file.write((char*)&best, sizeof(best));
		file.write((char*)&score, sizeof(score));
		file.write((char*)&winHappened, sizeof(winHappened));
		Save temp[M_TS][M_TS];
		for (int i = 0; i < tableSize; i++) {
			for (int j = 0; j < tableSize; j++) {
				temp[i][j].cellValue = cell[i][j];
				temp[i][j].vis = cell[i][j].visible;
			}
		}
		file.write((char*)&temp, sizeof(temp));
		file.close();
	}
}

void Game::draw(HDC hdc, POINT pos) {
	table.draw(hdc, pos, posCell, score, best);

	for (int i = 0; i < T_SIZE; i++)
		for (int j = 0; j < T_SIZE; j++)
			cell[i][j].draw(hdc);
}

void Game::calcPos(POINT pos, bool newGame) {

	table.UpdateTabel();

	pos.y += MULTIPLIER;
	rectScore = {
		pos.x + TABLE_SIZE_PIXELS - 2 * LABEL_SIZE.x - 2 * BORDER_SIZE,
		pos.y,
		pos.x + TABLE_SIZE_PIXELS,
		pos.y + LABEL_SIZE.y };


	pos.y += MULTIPLIER * 9;
	for (int i = 0; i < T_SIZE; i++) {
		for (int j = 0; j < T_SIZE; j++) {
			posCell[i][j].x = pos.x + (j + 1) * BORDER_SIZE + j * CELL_SIZE;
			posCell[i][j].y = pos.y + (i + 1) * BORDER_SIZE + i * CELL_SIZE;
			cell[i][j].pos = posCell[i][j];
		}
	}

	if (newGame) {
		if (start) {
			genCell();
			genCell();
			start = false;
		}
	}
}

void Game::updateColors() {
	table.UpdateTabel();
}

Game::CellPos Game::genCell() {
	std::vector<POINT> freeCell;  
	CellPos cellPos = { -10, -10, -10 };

	for (int i = 0; i < T_SIZE; i++)
		for (int j = 0; j < T_SIZE; j++)
			if (!cell[i][j].visible)
				freeCell.push_back({ i,j });


	if (freeCell.size()) {
		INT cellValue = rand() % 10;  
		INT p = rand() % freeCell.size();   
		INT i = freeCell[p].x;  
		INT j = freeCell[p].y;
		cell[i][j].visible = true;

		if (!cellValue)
		{
			cell[i][j].setCellValue(4);
			cellPos = { i, j, 4 };
		}
		else if (cell[i][j] != 2)
		{
			cell[i][j].setCellValue(2);
			cellPos = { i, j, 2 };
		}
		cellPos = { i, j, cell[i][j] };

		RECT rect = { posCell[i][j].x, posCell[i][j].y, posCell[i][j].x + CELL_SIZE, posCell[i][j].y + CELL_SIZE };
		InvalidateRect(hwnd, &rect, false);

		if (freeCell.size() == 1)
			checkMove();

		if (winHappened == 0) {
			checkEnd();
		}
	}
	return cellPos;
}

void Game::checkEnd() {
	for (int i = 0; i < T_SIZE; i++)
		for (int j = 0; j < T_SIZE; j++) {
			if ((cell[i][j].visible) && (cell[i][j] >= WINCONDITION)) {
				INT ans = MessageBoxW(hwnd, L"You win! Continue?", L"2048", MB_YESNO | MB_ICONQUESTION);
				if (ans == IDNO) {
					newGame();
				}
				if (ans == IDYES) {
					winHappened = 1;
				}
			}
		}
}

void Game::key(INT type) {
	if (!move) {

		if (type == VK_UP)
		{
			move.up = true;
		}

		if (type == VK_DOWN)
		{
			move.down = true;
		}

		if (type == VK_LEFT)
		{
			move.left = true;
		}

		if (type == VK_RIGHT) {
			move.right = true;
		}
	}

}

bool Game::step(INT si, INT sj, INT di, INT dj) {
	int s = 5;
	if (cell[di][dj].visible) {

		if (cell[si][sj] == cell[di][dj] && !checkbit(di, dj) && !checkbit(si, sj)) {
			cell[si][sj].visible = false;
			cell[di][dj].setCellValue(cell[si][sj] << 1);
			setbit(di, dj); 
			calcScore(cell[di][dj]);
			invalidRect(si, sj);
			invalidRect(di, dj);
			return true;
		}
		else
			return false;
	}
	else {

		cell[si][sj].visible = false;
		cell[di][dj].visible = true;
		cell[di][dj].setCellValue(cell[si][sj]);
		invalidRect(si, sj);
		invalidRect(di, dj);
		return true;
	}
}

bool Game::action(bool isNeedGenerate) {
	BOOLEAN act = false;

	if (move.up)
		for (int i = 1; i < T_SIZE; i++)
			for (int j = 0; j < T_SIZE; j++)
				if (cell[i][j].visible)     
					if (step(i, j, i - 1, j))
						act = true;

	if (move.down)
		for (int i = T_SIZE - 2; i >= 0; i--)
			for (int j = 0; j < T_SIZE; j++)
				if (cell[i][j].visible)
					if (step(i, j, i + 1, j))
						act = true;

	if (move.left)
		for (int j = 1; j < T_SIZE; j++)
			for (int i = 0; i < T_SIZE; i++)
				if (cell[i][j].visible)
					if (step(i, j, i, j - 1))
						act = true;

	if (move.right)
		for (int j = T_SIZE - 2; j >= 0; j--)
			for (int i = 0; i < T_SIZE; i++)
				if (cell[i][j].visible)
					if (step(i, j, i, j + 1))
						act = true;

	if (act)
		accessGen = true;  
	else if (move) {

		move.setFalse(); 
		accessUp = 0;      
		if (accessGen) {

			CellPos result = genCell();          

			accessGen = false;
		}
	}
	return act;
}

void Game::calcScore(INT s) {
	score += s;
	if (best < score)
		best = score;

	InvalidateRect(hwnd, &rectScore, false);
}

void Game::invalidRect(INT i, INT j) {
	RECT rect = { posCell[i][j].x, posCell[i][j].y, posCell[i][j].x + CELL_SIZE, posCell[i][j].y + CELL_SIZE };
	InvalidateRect(hwnd, &rect, false);
}

void Game::checkMove() {
	BOOLEAN issetMove = false;
	for (int i = 0; i < T_SIZE && !issetMove; i++) {
		for (int j = 0; j < T_SIZE && !issetMove; j++) {
			if (i && cell[i][j] == cell[i - 1][j])
				issetMove = true;
			if (i < T_SIZE - 1 && cell[i][j] == cell[i + 1][j])
				issetMove = true;
			if (j && cell[i][j] == cell[i][j - 1])
				issetMove = true;
			if (j < T_SIZE - 1 && cell[i][j] == cell[i][j + 1])
				issetMove = true;
		}
	}

	if (!issetMove) {
		INT ans = MessageBoxW(hwnd, L"You lost! Start again?", L"2048", MB_YESNO | MB_ICONQUESTION);
		if (ans == IDYES)
			newGame();
		else {
			newGame();
			DestroyWindow(hwnd);
		}
	}
}

void Game::newGame() {
	for (int i = 0; i < T_SIZE; i++) {
		for (int j = 0; j < T_SIZE; j++) {
			cell[i][j].visible = false;
		}
	}
	winHappened = 0;
	score = 0;
	genCell();
	genCell();
	RECT rect;
	GetClientRect(hwnd, &rect);
	InvalidateRect(hwnd, &rect, false);
}