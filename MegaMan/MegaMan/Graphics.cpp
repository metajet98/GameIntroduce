#include "Graphics.h"


Graphics*Graphics::instance = 0;
Graphics::Graphics(HWND hWnd)
{
	surface = 0;
	backBuffer = 0;
	sprite = 0;
	this->hWnd = hWnd;
	init();
}

Graphics * Graphics::getInstance()
{
	if (instance == 0)
		instance = new Graphics(WINDOW->getHandleWindow());
	return instance;
}


void Graphics::Release()
{
	if (d3ddv)
	{
		d3ddv->Release();
		d3ddv = 0;
	}

	if (surface)
	{
		surface->Release();
		surface = 0;
	}

	if (backBuffer)
	{
		backBuffer->Release();
		backBuffer = 0;
	}

	if (sprite)
	{
		sprite->Release();
		sprite = 0;
	}
}

LPDIRECT3DDEVICE9 Graphics::GetDevice()
{
	return d3ddv;
}

LPDIRECT3DSURFACE9 Graphics::GetBackBuffer()
{
	return backBuffer;
}

LPD3DXSPRITE Graphics::GetSprite()
{
	return sprite;
}


void Graphics::PrintText(const char * str, int size, int x, int y, DWORD color)
{
	ID3DXFont* dxfont;
	RECT textbox;
	SetRect(&textbox, x, y, 272, 272);
	// Initialize dxfont :
	D3DXCreateFont(d3ddv,    // the D3D Device
		size,    // font height
		0,    // default font width
		FW_NORMAL,    // font weight
		1,    // not using MipLevels
		false,    // italic font
		DEFAULT_CHARSET,    // default character set
		OUT_DEFAULT_PRECIS,    // default OutputPrecision,
		DEFAULT_QUALITY,    // default Quality
		DEFAULT_PITCH | FF_DONTCARE,    // default pitch and family
		"Arial",    // use Facename Arial
		&dxfont);    // the font object

	//Print text by dxfont object
	dxfont->DrawTextA(NULL,
		str,
		strlen(str),
		&textbox,
		DT_LEFT | DT_TOP,
		color);
	// Release dxfont object
	dxfont->Release();
}

void Graphics::BeginGraphics()
{
	HRESULT hr = d3ddv->BeginScene();
	HRESULT hr1 = sprite->Begin(D3DXSPRITE_ALPHABLEND);
	d3ddv->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(10, 10, 10), 1.0f, 0);
	if (FAILED(hr) || FAILED(hr1))
	{
		MessageBox(0, "Khong the bat dau ve", "Loi", MB_ICONERROR);
		PostQuitMessage(0);
	}
}

void Graphics::EndGraphics()
{
	HRESULT hr1 = sprite->End();
	HRESULT hr = d3ddv->EndScene();
	if (FAILED(hr) || FAILED(hr1))
	{
		MessageBox(0, "Khong the ket thuc ve", "Loi", MB_ICONERROR);
		PostQuitMessage(0);
	}
}

void Graphics::PresentBackBuffer()
{
	d3ddv->Present(0, 0, 0, 0);
}

Graphics::~Graphics()
{
}

bool Graphics::isInitDirectX()
{
	LPDIRECT3D9 d3d;
	if ((d3d = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return false;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = BACK_WIDTH;
	d3dpp.BackBufferHeight = BACK_HEIGHT;

	if (FAILED(d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv)))
	{
		return false;
	}

	if (d3ddv == NULL)
		return false;

	d3d->Release();

	return true;
}

bool Graphics::isInitSprite()
{
	HRESULT hr = D3DXCreateSprite(d3ddv, &sprite);
	return !FAILED(hr);
}

bool Graphics::isSetSurface()
{
	HRESULT hr = d3ddv->CreateOffscreenPlainSurface(SCREEN_WIDTH,
		SCREEN_HEIGHT,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&surface,
		0);
	return !FAILED(hr);
}

bool Graphics::isSetBackBuffer()
{
	HRESULT hr = d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO,
		&backBuffer);
	return !FAILED(hr);
}

void Graphics::init()
{
	if (!isInitDirectX() || !isInitSprite() || !isSetBackBuffer() || !isSetSurface())
		error();
}

void Graphics::error()
{
	MessageBox(hWnd, "Không the khoi tao graphics", "Loi", MB_ICONERROR);
	PostQuitMessage(0);
}
