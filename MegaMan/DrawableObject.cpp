#include "DrawableObject.h"
#include"TileMap.h"


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

void DrawableObject::setPauseAnimation(bool pauseAnimation)
{
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
	if (!alive) return;

	BaseObject::update();
	if (!pauseAnimation)
	{
		if (curAnimation == STAND)
		{
			delayAnimation.minFrameTime = 6 * ANIMATE_DELAY_TIME_DEFAULT;
			delayAnimation.maxFrameTime = 7 * ANIMATE_DELAY_TIME_DEFAULT;
		}
		else
		{
			delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT;
			delayAnimation.maxFrameTime = 2 * ANIMATE_DELAY_TIME_DEFAULT;
		}
		if (delayAnimation.canCreateFrame())
		{
			if (curFrame == sprite->animates[curAnimation].nFrame - 1)
			{
				if (curAnimation == JUMP || curAnimation == JUMP_SHOT || curAnimation == SLIDING || curAnimation == PUSHING_JUMP || curAnimation == ON_HIT || curAnimation == HIGH_JUMP)
				{
					curFrame = sprite->animates[curAnimation].nFrame - 1;
					return;
				}
				curFrame = 0;
			}
			else sprite->animates[curAnimation].next(curFrame);
		}
	}
}

void DrawableObject::draw()
{
	if (!alive)
		return;

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
