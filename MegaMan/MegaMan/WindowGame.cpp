#include "WindowGame.h"

WindowGame* WindowGame::instance = 0;

WindowGame * WindowGame::getInstance()
{
	if (instance == 0)
		instance = new WindowGame();
	return instance;
}

LRESULT WindowGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_QUIT:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void WindowGame::initHandleWindows(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = CLASS_NAME;
	RegisterClassEx(&wcex);

	HWND hWnd = CreateWindow(CLASS_NAME, TITLE_STR, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	this->hWnd = hWnd;
}

HWND WindowGame::getHandleWindow()
{
	return hWnd;
}

WindowGame::WindowGame()
{

}

WindowGame::~WindowGame()
{
}
