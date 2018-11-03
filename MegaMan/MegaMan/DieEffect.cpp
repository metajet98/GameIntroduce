#include "DieEffect.h"


List<DieEffect*>* DieEffect::list = 0;
List<DieEffect*>* DieEffect::getList()
{
	if (list == 0)
		list = new List<DieEffect*>();
	return list;
}

void DieEffect::draw()
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

void DieEffect::update()
{
	DrawableObject::update();
}

DieEffect::DieEffect(AFFECT_CATEGORY category)
{
	if (category == ROCK_DIE)
	{
		sprite = SPRITEMANAGER->sprites[SPR_ROCK_DIE];
	}
	vy = 0;
	vx = 0;
	ay = 0;
	getList()->_Add(this);
	collisionType = CT_NONE;
}

DieEffect::DieEffect()
{
}


DieEffect::~DieEffect()
{
}
