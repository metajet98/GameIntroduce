#include "Enermy.h"



void Enermy::update()
{
	/*if (damaged)
	{
		dx = 0;
		gameTimeLoop.canCreateFrame();

		if (gameTimeLoop.isTerminated())
			damaged = false;

		return;
	}*/

	if (alive)
		vx = direction * 40;

	MovableObject::update();
}

void Enermy::draw()
{

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

void Enermy::onCollision(BaseObject * other, int nx, int ny)
{
	MovableObject::onCollision(other, nx, ny);

}

void Enermy::onAABBCheck(BaseObject * other)
{
	if (other == ROCKMAN)
	{
		if (!ROCKMAN->onHit)
		{
			ROCKMAN->changeAction(ON_HIT);
			ROCKMAN->setOnHit(true);
			ROCKMAN->gameTimeLoop.start();
		}
	}
}

void Enermy::restore(BaseObject * obj)
{
	DrawableObject::restore(obj);
}

Enermy::Enermy()
{
	alive = true;
	count = 0;
	//vy = 0.5;
	collisionType = CT_ENERMY;
	gameTimeLoop.init(0.35, 1);
	gameTimeLoop.start();
}


Enermy::~Enermy()
{
}
