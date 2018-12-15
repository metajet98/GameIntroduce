#include "DoorCanMove.h"


List<DoorCanMove*>* DoorCanMove::instance = 0;
List<DoorCanMove*>* DoorCanMove::getInstance()
{
	if (instance == 0)
		instance = new List<DoorCanMove*>();
	return instance;
}

void DoorCanMove::draw()
{
	if (!alive)
	{
		dx = 0;
		dy = 0;
		ay = 0;
		if (timeDeath.canCreateFrame())
		{
			sprite = SPRITEMANAGER->sprites[SPR_ENEMY_DIE];
			curAnimation = 0;
			curFrame = (curFrame + 1) % 6;
		}

		if (timeDeath.isTerminated())
			return;

		int xInViewport, yInViewport;
		TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);
		sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
		return;
	}
	if (alive)
	{
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
}

void DoorCanMove::update()
{
	
}

void DoorCanMove::onCollision(BaseObject * S, int nx, int ny)
{
	if (S->collisionType == CT_PLAYER) COLLISION->preventMove(this, S);
}

void DoorCanMove::onAABBCheck(BaseObject * other)
{
}

void DoorCanMove::restore(BaseObject * obj)
{
	alive = true;
}

DoorCanMove::DoorCanMove()
{
}

DoorCanMove::DoorCanMove(int _x, int _y, int w, int h)
{
	timeDeath.init(0.2, 5);
	timeDeath.start();
	x = _x;
	y = _y;
	width = w;
	height = h;
	sprite = SPRITEMANAGER->sprites[SPR_DOOR_CAN_MOVE];
	direction = Left;
	collisionType = CT_DOOR_CAN_MOVE;
	DoorCanMove::getInstance()->_Add(this);
}


DoorCanMove::~DoorCanMove()
{
}
