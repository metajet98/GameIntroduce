#include "Mouse.h"


Mouse*Mouse::instance = 0;
Mouse*Mouse::getInstance()
{
	if (instance == 0)
		instance = new Mouse();
	return instance;
}

void Mouse::Create(HINSTANCE hInstance, HWND hWnd)
{
	instance = new Mouse(hInstance, hWnd);
}

void Mouse::PollMouse()
{
	dimouse->Poll();
	dimouse->GetDeviceState(sizeof(mouse_state), (LPVOID)&mouse_state);
}

void Mouse::updateMouse()
{

}

int Mouse::MouseX()
{
	return mouse_state.lX;
}

int Mouse::MouseY()
{
	return mouse_state.lY;
}

int Mouse::MouseButton(int button)
{
	return mouse_state.rgbButtons[button] & 0x80;
}

void Mouse::Release()
{
	if (dimouse)
	{
		dimouse->Unacquire();
		dimouse->Release();
		dimouse = NULL;
	}

	if (diput)
	{
		diput->Release();
		diput = 0;
	}
}

Mouse::Mouse(HINSTANCE hInstance, HWND hWnd)
{
	this->hInstance = hInstance;
	this->hWnd = hWnd;
	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&diput, NULL);
	diput->CreateDevice(GUID_SysMouse, &dimouse, NULL);
	dimouse->SetDataFormat(&c_dfDIMouse);
	dimouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 1024;

	dimouse->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	dimouse->Acquire();

}
Mouse::Mouse()
{

}


Mouse::~Mouse()
{
}
