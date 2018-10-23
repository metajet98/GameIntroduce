#include "DrawableObject.h"



void DrawableObject::setSprite()
{
	sprite = SPRITEMANAGER->sprites[id % 100];
}

void DrawableObject::setPauseAnimation(bool pauseAnimation, int frameIndex)
{
	if (pauseAnimation)
		curFrame = frameIndex;

	this->pauseAnimation = pauseAnimation;
}

void DrawableObject::changeAction(int newAction)
{
	if (curAnimation != newAction)
	{
		nextAnimation = newAction;
	}
		
}

void DrawableObject::update()
{
	BaseObject::update();
	if (delayAnimation.canCreateFrame())
	{
		if (curFrame == sprite->animates[curAnimation].nFrame - 1)
		{
			if (curAnimation == JUMP || curAnimation == JUMP_SHOT || curAnimation==SLIDING || curAnimation== PUSHING_JUMP || curAnimation==APPEAR)
			{
				curFrame = sprite->animates[curAnimation].nFrame - 1;
				return;
			}
			curFrame = 0;
		}
		else sprite->animates[curAnimation].next(curFrame);
	}
}

void DrawableObject::draw()
{

}

void DrawableObject::restore(BaseObject * obj)
{
	setSprite();
	OldRestore::restore(obj);
	alive = true;
	curAnimation = 0;
	nextAnimation = 0;
	curFrame = 0;
}

DrawableObject::DrawableObject()
{
	sprite = 0;
	curAnimation = 0;
	nextAnimation = 0;
	curFrame = 0;
	delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT;
	delayAnimation.maxFrameTime = 2 * ANIMATE_DELAY_TIME_DEFAULT;
	pauseAnimation = false;
	alive = true;
}


DrawableObject::~DrawableObject()
{
}
