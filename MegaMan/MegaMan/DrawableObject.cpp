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
		nextAnimation = newAction;
}

void DrawableObject::update()
{

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
