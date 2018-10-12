#pragma once
#include"Graphics.h"


class Texture
{
private:
	LPDIRECT3DTEXTURE9 texture;

public:
	int Width, Height;
	Direction direction;
	Texture(const char* filepath, D3DCOLOR transColor);
	void Init(const char* filepath, D3DCOLOR transColor);
	void RenderTexture(int x, int y, RECT *r);

	void render(LPD3DXSPRITE spriteHandle, RECT * srcRect, D3DXVECTOR2 position, D3DXVECTOR2 scale, float rotate, D3DXVECTOR2 origin, float zIndex);
	Texture();
	~Texture();
};

