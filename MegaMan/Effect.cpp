#include "Effect.h"


List<Effect*>* Effect::instance = 0;
List<Effect*>* Effect::getInstance()
{
	if (instance == 0)
		instance = new List<Effect*>();
	return instance;
}

void Effect::draw()
{
	if (sprite == 0) return;

	int xInViewport, yInViewport;
	TileMap::curMap->convertToViewportPos(this->x, this->y, xInViewport, yInViewport);

	int trucQuay = xInViewport + width / 2;

	if (direction == sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		mt._41 = 2 * trucQuay;
		mt._11 = -1;
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}

	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);

	if (direction == sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}
}

void Effect::update()
{
	if (!alive) return;

	BaseObject::update();
	if (!pauseAnimation)
	{
		if (delayAnimation.canCreateFrame())
		{
			if (curFrame > sprite->animates[curAnimation].nFrame - 1)
			{
				this->allowDelete = true;
			}
			else sprite->animates[curAnimation].next(curFrame);
		}
	}
}

Effect::Effect()
{

}


Effect::~Effect()
{
}
