#include "Texture.h"



Texture::Texture(const char * filepath, D3DCOLOR transColor)
{
	Init(filepath, transColor);
}

void Texture::Init(const char * filepath, D3DCOLOR transColor)
{
	direction = Left;
	HRESULT result;
	D3DXIMAGE_INFO info;
	result = D3DXGetImageInfoFromFile(filepath, &info);
	Width = info.Width;
	Height = info.Height;
	if (result != D3D_OK)
	{
		MessageBox(WINDOW->getHandleWindow(), "(1)Không the khoi tao TEXTURE", "Loi", MB_ICONERROR);
		PostQuitMessage(0);
	}

	result = D3DXCreateTextureFromFileEx(
		GRAPHICS->GetDevice(),
		filepath,
		info.Width,
		info.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transColor,
		&info,
		NULL,
		&texture);

	if (result != D3D_OK)
	{
		MessageBox(WINDOW->getHandleWindow(), "(2)Không the khoi tao TEXTURE", "Loi", MB_ICONERROR);
		PostQuitMessage(0);
	}
}

void Texture::RenderTexture(int x, int y, RECT * r)
{
	GRAPHICS->GetSprite()->Draw(
		texture,
		r,
		0,
		&D3DXVECTOR3((float)x, (float)y, 0),
		D3DCOLOR_XRGB(255, 255, 255)
	);
}

void Texture::render(LPD3DXSPRITE spriteHandle, RECT * srcRect, D3DXVECTOR2 position, D3DXVECTOR2 scale, float rotate, D3DXVECTOR2 origin, float zIndex)
{
	D3DXMATRIX matFinal;
	D3DXMATRIX matTransformed;
	D3DXMATRIX matOld;

	// origin in position
	D3DXVECTOR3 center = D3DXVECTOR3(abs(srcRect->right - srcRect->left) * origin.x, abs(srcRect->top - srcRect->bottom) * (1 - origin.y), zIndex);

	// get matrix texture
	spriteHandle->GetTransform(&matOld);

	D3DXMatrixTransformation2D(
		&matTransformed,						// ma tran ket qua sau transform
		&position,								// goc toa do / diem neo
		0.0f,
		&scale,									// ti le scale
		&position,								// goc toa do / diem neo
		D3DXToRadian(rotate),					// góc xoay theo radian
		0										// vi trí
	);

	matFinal = matTransformed * matOld;

	//set matrix transformed
	spriteHandle->SetTransform(&matFinal);

	// BEGIN
	spriteHandle->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_DONOTSAVESTATE);

	spriteHandle->Draw(
		this->texture,
		srcRect,
		&center,
		&D3DXVECTOR3(position.x, position.y, zIndex),
		D3DCOLOR_XRGB(255, 255, 255));

	spriteHandle->SetTransform(&matOld);

	// END
	spriteHandle->End();
}

Texture::Texture()
{
}

Texture::~Texture()
{
}
