#include "Enermy.h"



void Enermy::update()
{
	if (damaged)
	{
		dx = 0;
		gameTimeLoop.canCreateFrame();

		if (gameTimeLoop.isTerminated())
			damaged = false;

		return;
	}

	if (alive)
		vx = direction * 40;

	MovableObject::update();
}

void Enermy::draw()
{
	if (!alive)
	{
		if (timeDeath.canCreateFrame())
		{
			sprite = SPRITEMANAGER->sprites[SPR_ENEMY_DIE];
			curAnimation = 0;
			curFrame = (curFrame + 1) % 3;
			vx = 0;
		}

		if (timeDeath.isTerminated())
			return;

		int xInViewport, yInViewport;
		TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);
		sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
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

void Enermy::onCollision(BaseObject * other, int nx, int ny)
{
	MovableObject::onCollision(other, nx, ny);
}

void Enermy::onAABBCheck(BaseObject * other)
{
	if (other == ROCKMAN)
	{
		if (!ROCKMAN->onHit && !ROCKMAN->invisible)
		{
			ROCKMAN->changeAction(ON_HIT);
			ROCKMAN->setOnHit(true);
			ROCKMAN->life -= damage;
			ROCKMAN->gameTimeLoop.start();
			
		}
	}
	if (other->collisionType == CT_BUTLET)
	{
		if (!damaged)
		{
			damaged = true;
			this->life --;
			other->allowDelete = true;
			gameTimeLoop.start();
		}
	
		if (life <= 0) this->alive = false;
	}
}

void Enermy::restore(BaseObject * obj)
{
	DrawableObject::restore(obj);
	timeDeath.start();
}

Enermy::Enermy()
{
	alive = true;
	count = 0;
	//vy = 0.5;
	collisionType = CT_ENERMY;
	gameTimeLoop.init(0.4, 1);
	gameTimeLoop.start();
	damage = 23;
	damaged = false;
	timeDeath.init(0.2, 4);
	timeDeath.start();
}


Enermy::~Enermy()
{
}
