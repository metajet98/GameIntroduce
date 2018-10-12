#include "Rockman.h"


Rockman* Rockman::instance = 0;
Rockman * Rockman::getInstance()
{

	if (instance == 0)
		instance = new Rockman();
	return instance;
}

void Rockman::onCollision(BaseObject*S, int nx, int ny)
{
	MovableObject::onCollision(S,nx,ny);
}

void Rockman::updateLocation()
{
	x += dx;
	y += dy;
}



void Rockman::draw()
{	
	int xInViewport, yInViewport;
	TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);

	sprite->draw(xInViewport, yInViewport, curAnimation, 0);
}

void Rockman::changeAction(int newAction)
{
	DrawableObject::changeAction(newAction);

	if (curAnimation != newAction)
	{
		curAnimation = newAction;
	}
}

void Rockman::update()
{
	if (KEY->keyLeft) 
		direction = Left;
	if(KEY->keyRight)
	{
		direction = Right;
		changeAction(MOVE);
	}
	if (KEY->keyMove)
	{
		vx = ROCKMAN_VX_GO * direction;
	}
	else
	{
		vx = 0;
		changeAction(STAND);
	}
	//if (isOnGround)
	{
		if (KEY->keyJum)
		{
			vy = -150;
			changeAction(JUMP);
		}
	}
	MovableObject::update();
}

Rockman::Rockman()
{
	sprite = SPRITEMANAGER->sprites[SPR_MAIN];
	x = 124;
	y = 673;
	width = 38;
	height = 40;
}


Rockman::~Rockman()
{
}
