#include "framework.h"
#include "2048.h"
#include "vars.h"
#include "dwmapi.h"

PAINTSTRUCT ps;
HDC hdcMem;
HDC hdc;
HBITMAP hbmMem;
HBRUSH hbrBkGnd;
HGDIOBJ hbmOld;
POINT pos;
Game* game;

bool isClicked = false;
long xClicked;
long yClicked;

void createGame(HWND hwnd, int new_t_size);
void newGame(HWND hwnd, int new_t_size);
void changeMultiplier(HWND hwnd, int newMultiplier);
void updateClientArea(HWND hwnd);
void changeTheme(HWND hwnd, int newTheme);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, INT nCmdShow) {

	const wchar_t CLASS_NAME[] = L"2048";
	const wchar_t menu[] = L"IDC_MY2048";

	WNDCLASSEX wc = { };

	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.lpfnWndProc = WindowProc;
	wc.hbrBackground = CreateSolidBrush(STANDART_BG_COLOR);

	wc.lpszMenuName = MAKEINTRESOURCEW(IDC_MY2048);

	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2048));;
	wc.hIconSm = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_MY2048));;
	wc.hCursor = LoadCursor(nullptr, IDC_HAND);

	wc.style = NULL;
	wc.cbSize = sizeof(wc);

	RegisterClassExW(&wc);

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		wc.lpszClassName,               // Window class
		L"2048",    // Window text
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,            // Window style

		// Size and position
		200,
		200,
		TABLE_SIZE_PIXELS + 4 * MULTIPLIER,
		TABLE_SIZE_PIXELS + 2 * BORDER_SIZE + LABEL_SIZE.y + 10 * MULTIPLIER,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg)
	{
	case WM_CREATE:
	{
		createGame(hwnd, T_SIZE);

		srand((UINT)time(NULL));
		SetTimer(hwnd, 1, 20, NULL);
		break;
	}

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);

		switch (wmId)
		{
		case ID_NEWGAME_3X3:
		{
			newGame(hwnd, 3);
			break;
		}

		case ID_NEWGAME_4X4:
		{
			newGame(hwnd, 4);
			break;
		}

		case ID_NEWGAME_5X5:
		{
			newGame(hwnd, 5);
			break;
		}

		case ID_NEWGAME_6X6:
		{
			newGame(hwnd, 6);
			break;
		}

		case ID_GAME_EXIT:
		{
			DestroyWindow(hwnd);
			break;
		}

		case ID_CHANGE_CELL_SIZE_SMALL:
		{
			changeMultiplier(hwnd, 6);
			break;
		}

		case ID_CHANGE_CELL_SIZE_NORMAL:
		{
			changeMultiplier(hwnd, 8);
			break;
		}

		case ID_CHANGE_CELL_SIZE_BIG:
		{
			changeMultiplier(hwnd, 10);
			break;
		}

		case ID_CHANGETHEME_DEFAULT:
		{
			changeTheme(hwnd, 1);
			break;
		}
		case ID_CHANGETHEME_GREEN: {
			changeTheme(hwnd, 2);
			break;
		}

		case ID_CHANGETHEME_BLUE:
		{
			changeTheme(hwnd, 3);
			break;
		}
		case ID_NEWGAME: {
			newGame(hwnd, T_SIZE);
		}

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		break;
	}

	case WM_SIZE:
	{
		pos = { MULTIPLIER, MULTIPLIER };
		game->calcPos(pos, true);
		break;
	}

	case WM_TIMER:
		game->action(true);
		break;

	case WM_ERASEBKGND:
		return (LRESULT)1; 

	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);

		RECT rc;
		GetClientRect(hwnd, &rc);

		hdcMem = CreateCompatibleDC(ps.hdc);
		hbmMem = CreateCompatibleBitmap(ps.hdc, rc.right - rc.left, rc.bottom - rc.top);

		hbmOld = SelectObject(hdcMem, hbmMem);

		hbrBkGnd = CreateSolidBrush(STANDART_BG_COLOR);
		FillRect(hdcMem, &rc, hbrBkGnd);
		DeleteObject(hbrBkGnd);

		game->draw(hdcMem, pos);

		BitBlt(ps.hdc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, hbmOld);
		DeleteObject(hbmMem);
		DeleteDC(hdcMem);

		EndPaint(hwnd, &ps);
		break;
	}

	case WM_LBUTTONDOWN:
	{
		xClicked = LOWORD(lParam); 
		yClicked = HIWORD(lParam);

		isClicked = true;

		break;
	}


	case WM_LBUTTONUP:
	{
		long x = LOWORD(lParam);
		long y = HIWORD(lParam);

		long moveW = x - xClicked; 
		long moveH = y - yClicked; 

		if (isClicked && ((abs(moveW) > 50) || (abs(moveH) > 50))) {
			if (moveW <= 0) {

				if (abs(moveW) >= abs(moveH)) {
					game->key(VK_LEFT);
				}
				else {
					if (moveH <= 0) {
						game->key(VK_UP);
					}
					else
					{
						game->key(VK_DOWN);
					}
				}
			}
			else {
				if (abs(moveW) >= abs(moveH)) {
					game->key(VK_RIGHT);
				}
				else {
					if (moveH <= 0) {
						game->key(VK_UP);
					}
					else
					{
						game->key(VK_DOWN);
					}
				}
			}
		}

		isClicked = false;
		break;
	}

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_UP:
			game->key(VK_UP);
			break;

		case VK_DOWN:
			game->key(VK_DOWN);
			break;

		case VK_LEFT:
			game->key(VK_LEFT);
			break;

		case VK_RIGHT:
			game->key(VK_RIGHT);
			break;

		case VK_F5:
			newGame(hwnd, T_SIZE);
			break;

		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	}

	case WM_DESTROY:
		delete(game);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

void updateClientArea(HWND hwnd) {

	int x = 30;
	int y = 15;

	switch (MULTIPLIER)
	{
	case 6:
	{
		x = 25;
		y = 15;
		break;
	}
	case 10:
	{
		x = 30;
		y = -5;
		break;
	}
	case 8:
	{
		x = 28;
		y = 5;
		break;
	}
	default:
		break;
	}

	RECT rc;
	rc.left = 0;
	rc.right = TABLE_SIZE_PIXELS + x;
	rc.top = 0;
	rc.bottom = TABLE_SIZE_PIXELS + 10 * MULTIPLIER + LABEL_SIZE.y + y;

	AdjustWindowRect(&rc, NULL, TRUE);

	SetWindowPos(hwnd, NULL,
		(GetSystemMetrics(SM_CXSCREEN) - (rc.right - rc.left)) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - (rc.bottom - rc.top)) / 2,
		rc.right - rc.left,
		rc.bottom - rc.top,
		SWP_NOZORDER);

	RECT rect;
	GetClientRect(hwnd, &rect);
	InvalidateRect(hwnd, &rect, false);
}

void createGame(HWND hwnd, int new_t_size) {

	int old_t_size = T_SIZE;

	T_SIZE = new_t_size;

	game = new Game(hwnd, T_SIZE, MULTIPLIER);

	updateClientArea(hwnd);
}

void newGame(HWND hwnd, int new_t_size) {

	if (new_t_size == T_SIZE) {
		INT ans = MessageBoxW(hwnd, L"Start new game?", L"2048", MB_YESNO | MB_ICONQUESTION);
		if (ans == IDYES) {
			game->newGame();
		}
	}
	else {
		delete(game);
		createGame(hwnd, new_t_size);
		updateClientArea(hwnd);
	}
}

void changeMultiplier(HWND hwnd, int newMultiplier) {
	MULTIPLIER = newMultiplier;
	CalculateConsts(T_SIZE, MULTIPLIER);
	game->calcPos({ MULTIPLIER, MULTIPLIER }, false);
	updateClientArea(hwnd);
}

void changeTheme(HWND hwnd, int newTheme) {
	ChangeColors(newTheme);
	game->updateColors();
	updateClientArea(hwnd);
}