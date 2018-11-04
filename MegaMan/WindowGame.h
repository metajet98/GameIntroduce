#pragma once
#include<Windows.h>
#include"Constant.h"
class WindowGame
{
private:
	HWND hWnd;

	static WindowGame*instance;

	WindowGame();
public:
	static WindowGame* getInstance();

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	void initHandleWindows(HINSTANCE hInstance, int nCmdShow);
	HWND getHandleWindow();

	~WindowGame();
};

