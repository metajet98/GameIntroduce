#include "Effect_Power.h"


Effect_Power * Effect_Power::instance = 0;
Effect_Power * Effect_Power::getInstance()
{
	if (instance == 0)
		instance = new Effect_Power();
	return instance;
}

void Effect_Power::draw()
{
	if (sprite == 0) return;

	int xInViewport, yInViewport;
	TileMap::curMap->convertToViewportPos(this->x, this->y, xInViewport, yInViewport);
	int trucQuay = xInViewport + width / 2;

	/*if (direction == sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		mt._41 = 2 * trucQuay;
		mt._11 = -1;
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}*/
	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
	/*if (direction == sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}*/
}

void Effect_Power::update()
{
	DrawableObject::update();
	dx = ROCKMAN->dx;
	dy = ROCKMAN->dy;
	updateLocation();
}

Effect_Power::Effect_Power()
{
	sprite = SPRITEMANAGER->sprites[SPR_BULLET_STRONG];
	vy = 0;
	vx = 0;
	ay = 0;
	//direction = ROCKMAN->direction;
	/*x = ROCKMAN->xCenter() - width/2;
	y = ROCKMAN->yCenter() - height/2;*/
	width = 32;
	height = 32;
}


Effect_Power::~Effect_Power()
{
}
