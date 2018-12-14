#include "Door.h"



void Door::draw()
{
	DrawableObject::draw();
}

void Door::update()
{
	if (!updating)
		return;

	if (ROCKMAN->x >= this->right())
	{
		Close();
	}
}

void Door::updateFrame()
{
	if (sprite == 0) return;

	if (!pauseAnimation)
	{
		if (delayAnimation.canCreateFrame())
		{
			if (curFrame == sprite->animates[curAnimation].nFrame - 1)
			{
				curFrame == sprite->animates[curAnimation].nFrame - 1;
			}
			else sprite->animates[curAnimation].next(curFrame);
		}
	}
	if (curFrame == sprite->animates[curAnimation].nFrame - 1)
	{
		if (curAnimation == 0)
		{
			ROCKMAN->x += 2*ROCKMAN->direction;
			pauseAnimation = true;
			isClose = false;
		}
		if (curAnimation == 1)
		{
			isClose = true;
		}
		//pauseAnimation = true;
	}
}

void Door::Open()
{
	curAnimation = 0;
	updateFrame();
}

void Door::Close()
{
	curAnimation = 1;
	pauseAnimation = false;
	ROCKMAN->pauseAnimation = false;
	updateFrame();
}

void Door::onCollision(BaseObject * S, int nx, int ny)
{
	MovableObject::onCollision(S, nx, ny);
}
void Door::onAABBCheck(BaseObject * other)
{
	if (other == ROCKMAN)
	{
		updating = true;
		ROCKMAN->pauseAnimation = true;
		if (ROCKMAN->direction == Right)
		{
			ROCKMAN->dx = 0;
			Open();
		}
		else
		{
			ROCKMAN->dx = 0;
			COLLISION->preventMove(other, this);
		}
	}
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
