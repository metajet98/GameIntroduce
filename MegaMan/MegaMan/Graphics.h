#pragma once
#include "Constant.h"
#include "WindowGame.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

class Graphics
{
private:
	LPDIRECT3DDEVICE9 d3ddv; // Công cụ vẽ
	LPDIRECT3DSURFACE9 surface;
	LPDIRECT3DSURFACE9 backBuffer;
	LPD3DXSPRITE sprite;
	HWND hWnd;

	bool isInitDirectX();     //Create DirectX device
	bool isInitSprite(); //Create Sprite
	bool isSetSurface(); // Create surface
	bool isSetBackBuffer(); // GetBackBuffer
	void init();
	void error();

	static Graphics*instance;
	Graphics(HWND hWnd);

public:
	static Graphics* getInstance();

	void Release();
	LPDIRECT3DDEVICE9 GetDevice();
	LPDIRECT3DSURFACE9 GetBackBuffer();
	LPD3DXSPRITE GetSprite();

	void PrintText(const char* str, int size, int x, int y, DWORD color);
	void BeginGraphics();
	void EndGraphics();
	void PresentBackBuffer();

	~Graphics();
};

