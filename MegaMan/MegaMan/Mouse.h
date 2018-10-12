#pragma once
#include<dinput.h>
#include<dinput.h>

class Mouse
{
private:
	HWND hWnd;
	HINSTANCE hInstance;
	LPDIRECTINPUT8 diput;
	LPDIRECTINPUTDEVICE8 dimouse;
	DIMOUSESTATE mouse_state;
	Mouse(HINSTANCE hInstance, HWND hWnd);

	static Mouse*instance;
public:
	static Mouse*getInstance();
	static void Create(HINSTANCE, HWND);
	void PollMouse();
	void updateMouse();
	int MouseX();
	int MouseY();
	int MouseButton(int button);
	void Release();
	Mouse();
	~Mouse();
};

