#include "Enermy.h"
#include"HP_bar.h"


void Enermy::update()
{
	if (damaged)
	{
	/*	dx = 0;
		gameTimeLoop.canCreateFrame();

		if (gameTimeLoop.isTerminated())
			damaged = false;*/
		damaged = false;

		return;
	}

	if (alive)
	{
		vx = direction * 40;
		MovableObject::update();
	}


}

void Enermy::draw()
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
			AudioManager::getInstance()->Play(AUDIO_CREP_DIE);
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
	else if (other->collisionType == CT_BUTLET)
	{
		
		RockButlet* r = (RockButlet*)other;
		if (r->categoryBullet != OF_STRONG_2_MEGAMAN)
			other->allowDelete = true;
		if (!damaged)
		{
			damaged = true;
			if (r->categoryBullet == OF_STRONG_MEGAMAN)
				this->life -= 2;
			else if(r->categoryBullet == OF_STRONG_2_MEGAMAN)
				this->life -= 3;
			else this->life--;
			
			//gameTimeLoop.start();
		}

		if (life <= 0)
		{
			this->alive = false;
		}
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
	/*gameTimeLoop.init(0.1, 1);
	gameTimeLoop.start();*/
	damage = 2;
	damaged = false;
	timeDeath.init(0.2, 5);
	timeDeath.start();
}


Enermy::~Enermy()
{
}
