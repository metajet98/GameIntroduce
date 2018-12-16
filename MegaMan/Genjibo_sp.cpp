#include "Genjibo_sp.h"


Genjibo_sp * Genjibo_sp::instance = 0;
Genjibo_sp * Genjibo_sp::getInstance()
{
	if (instance == 0) 
		instance = new Genjibo_sp();
	return instance;
}

void Genjibo_sp::draw()
{
	if (alive)
	{
		int deltaX = width - sprite->animates[curAnimation].frames[curFrame].width;
		int deltaY = height - sprite->animates[curAnimation].frames[curFrame].height;
		int xInViewport, yInViewport;
		TileMap::curMap->convertToViewportPos(x + deltaX / 2, y + deltaY / 2, xInViewport, yInViewport);
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
}

void Genjibo_sp::update()
{
	if (!ROCKMAN->onAreaBossSub) return;
	
	if (!GENJIBO->updating)
	{
		ROCKMAN->dx = 0;
		ROCKMAN->dy = 1;
	}
	
	vy = direction * 50;
	if (bottom() >= 390)
	{
		vy = 0;
		timeStand.canCreateFrame();
		if (timeStand.isTerminated())
		{
			GENJIBO->updating = true;
			direction = Left;
			vy = direction * 50;
		}
	}
	 
	updateMove();
}

void Genjibo_sp::restore(BaseObject * obj)
{
	if (ROCKMAN->onAreaBossSub && GENJIBO->alive) return;
	x = 431;
	y = 289;
	alive = true;
	direction = Right;
	curAnimation = 0;
	curFrame = 0;
	timeStand.start();
}

void Genjibo_sp::updateMove()
{
	if (!alive) return;
	//isOnGround = false;
	updateVerlocity();
	BaseObject::update();
	if (!pauseAnimation)
	{
		if (curFrame == sprite->animates[curAnimation].nFrame - 1)
		{
			curFrame = 0;
		}
		else sprite->animates[curAnimation].next(curFrame);
	}
}

Genjibo_sp::Genjibo_sp()
{
	sprite = SPRITEMANAGER->sprites[SPR_GENJIBO_SP];
	direction = Right;
	curAnimation = 0;
	curFrame = 0;
	timeStand.init(0.2, 5);
	timeStand.start();
	isActive = false;
	ay = 0;
}


Genjibo_sp::~Genjibo_sp()
{
}
