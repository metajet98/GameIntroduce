#include "KeyBoard.h"


KeyBoard* KeyBoard::instance = 0;

KeyBoard * KeyBoard::getInstance()
{
	if (instance == 0)
		instance = new KeyBoard();
	return instance;
}
void KeyBoard::Create(HINSTANCE hInstance, HWND hWnd)
{
	instance = new KeyBoard(hInstance, hWnd);
}
void KeyBoard::updateKeyBoard()
{
	BYTE keys[256];
	dinputdv->GetDeviceState(256, keys);

	for (int i = 0; i < 256; i++)
	{
		keyStates[i] = keys[i];
	}
}
void KeyBoard::PollKeyboard()
{
	dinputdv->Poll();
	if (FAILED(dinputdv->GetDeviceState(sizeof(keyEvents), (LPVOID)&keyEvents)))
	{
		//keyboard device lost, try to re-acquire
		dinputdv->Acquire();
		dinputdv->GetDeviceState(sizeof(keyEvents), (LPVOID)&keyEvents);
	}
	else
		dinputdv->GetDeviceState(sizeof(keyEvents), (LPVOID)&keyEvents);
}
bool KeyBoard::IsKeyDown(BYTE keycode)
{
	return (keyStates[keycode] & 0x80) > 0;
}
bool KeyBoard::IskeyUp(BYTE keycode)
{
	return (keyStates[keycode] & 0x80) > 0;
}
void KeyBoard::Release()
{
	if (dinputdv)
	{
		dinputdv->Unacquire();
		dinputdv->Release();
		dinputdv = NULL;
	}

	if (dinput)
	{
		dinput->Release();
		dinput = 0;
	}
}
KeyBoard::KeyBoard(HINSTANCE hInstance, HWND hWnd)
{
	this->hInstance = hInstance;
	this->hWnd = hWnd;
	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&dinput, NULL);
	dinput->CreateDevice(GUID_SysKeyboard, &dinputdv, NULL);
	dinputdv->SetDataFormat(&c_dfDIKeyboard);
	dinputdv->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 1024;

	dinputdv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	dinputdv->Acquire();
	for (int i = 0; i < 256; i++)
	{
		keyStates[i] = 0x00;
	}
}

KeyBoard::KeyBoard()
{
}


KeyBoard::~KeyBoard()
{
}
