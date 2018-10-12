#pragma once
#include<dinput.h>
#include<dinput.h>


class KeyBoard
{
private:
	HWND hWnd;
	HINSTANCE hInstance;
	LPDIRECTINPUT8 dinput;
	LPDIRECTINPUTDEVICE8	dinputdv;
	DIDEVICEOBJECTDATA keyEvents[256];
	bool pressed[256];
	BYTE keyStates[256];
	KeyBoard(HINSTANCE hInstance, HWND hWnd);

	static KeyBoard*instance;
public:
	static KeyBoard*getInstance();

	static void Create(HINSTANCE hInstance, HWND hWnd);
	void updateKeyBoard();
	void PollKeyboard();
	bool IsKeyDown(BYTE keycode);
	bool IskeyUp(BYTE keycode);
	void Release();

	KeyBoard();
	~KeyBoard();
};

