#include "Door.h"



void Door::draw()
{
	DrawableObject::draw();
}

void Door::update()
{
	if (sprite == 0) return;

	if (!pauseAnimation)
	{
		if (delayAnimation.canCreateFrame())
		{
			sprite->animates[curAnimation].next(curFrame);
		}
	}
	if (curFrame == sprite->animates[curAnimation].nFrame - 1)
	{
		if (curAnimation == 0)
		{
			ROCKMAN->dx = ROCKMAN->direction;
			pauseAnimation = true;
			isClose = false;
		}
		if (curAnimation == 1)
		{
			isClose = true;
			//isOpen = false;
		}
		//pauseAnimation = true;
	}
}

void Door::Open()
{
	curAnimation = 0;
	update();
}

void Door::Close()
{
	curAnimation = 1;
	pauseAnimation = false;
	ROCKMAN->pauseAnimation = false;
	update();
}

void Door::onCollision(BaseObject * S, int nx, int ny)
{
	
}
void Door::onAABBCheck(BaseObject * other)
{
	
}

Door::Door()
{
	sprite = SPRITEMANAGER->sprites[SPR_DOOR];
	direction = Left;
	collisionType = CT_DOOR;
	delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT;
	delayAnimation.maxFrameTime = 2 * ANIMATE_DELAY_TIME_DEFAULT;
}

Door::Door(int x, int y, int w, int h)
{
	sprite = SPRITEMANAGER->sprites[SPR_DOOR];
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
	direction = Left;
	collisionType = CT_DOOR;
	pauseAnimation = false;
	delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT;
	delayAnimation.maxFrameTime = 2 * ANIMATE_DELAY_TIME_DEFAULT;
}


Door::~Door()
{
}
