#include "LifeUI.h"


LifeUI* LifeUI::instance = 0;
LifeUI * LifeUI::getInstance()
{
	if (instance == 0)
		instance = new LifeUI();
	return instance;
}

void LifeUI::next(int & curFrame)
{
}

void LifeUI::draw()
{
	if (sprite == 0)
		return;

	int xInViewport, yInViewport;
	TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);
	int trucQuay = xInViewport + width / 2;

	if (direction != sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		mt._41 = 2 * trucQuay;
		mt._11 = -1;
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}

	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);

	if (direction != sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}
}

void LifeUI::updateLocation()
{
	x = Map::curMap->xMap+5;
	y = Map::curMap->yMap+5;
}

LifeUI::LifeUI()
{
}


LifeUI::~LifeUI()
{
}
