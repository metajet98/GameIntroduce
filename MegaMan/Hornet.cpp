#include "Hornet.h"


List<Hornet*>* Hornet::instance = 0;
List<Hornet*>* Hornet::getInstance()
{
	if (instance == 0) instance = new List<Hornet*>();
	return instance;
}

void Hornet::draw()
{
	if (!alive)
	{
		dx = 0;
		dy = 0;
		ay = 0;
		if (timeDeath.canCreateFrame())
		{
			sprite = SPRITEMANAGER->sprites[SPR_HORNET_DIE];
			curAnimation = 0;
			curFrame = (curFrame + 1) % 6;
			AudioManager::getInstance()->Play(AUDIO_CREP_DIE);
		}

		if (timeDeath.isTerminated())
		{
			Hornet::getInstance()->_Remove(this);
			return;
		}

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

void Hornet::update()
{
	if (damaged)
	{
		damaged = false;
		return;
	}
	
	timeDie.curLoop++;
	if (timeDie.curLoop>=300) alive = false;
	if (alive)
	{
		if (type == 2)
		{
			vx = ROCKMAN->x - this->x;
			vy = ROCKMAN->y - this->y;
			if (vx == 0 && vy == 0)
			{
				x = ROCKMAN->x;
				y = ROCKMAN->y;
			}
		}
	}
	MovableObject::update();
}

void Hornet::onCollision(BaseObject * other, int nx, int ny)
{
	MovableObject::onCollision(other, nx, ny);
	if ((ny!=0 || nx != 0) && (other->collisionType == CT_GROUND || other->collisionType == CT_DOOR || other->collisionType == CT_DOOR_CAN_MOVE))
	{
		vx = 0;
		vy = 0;

	}
}

void Hornet::onAABBCheck(BaseObject * other)
{
	if (other == ROCKMAN && !ROCKMAN->onHit && !ROCKMAN->invisible)
	{
		ROCKMAN->changeAction(ON_HIT);
		ROCKMAN->setOnHit(true);
		ROCKMAN->life -= 1;
		ROCKMAN->gameTimeLoop.start();
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
			else if (r->categoryBullet == OF_STRONG_2_MEGAMAN)
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

Hornet::Hornet(int xBoss, int yBoss, Direction dirBoss, int _vx, int _vy,int _type)
{
	sprite = SPRITEMANAGER->sprites[SPR_HORNET];
	alive = true;
	x = xBoss;
	y = yBoss + 18;
	damage = 1;
	ay = 0;
	vx = _vx;
	vy = _vy;
	direction = dirBoss;
	curAnimation = 0;
	curFrame = 0;
	Hornet::getInstance()->_Add(this);
	collisionType = CT_ENERMY;
	width = 15;
	height = 15;
	timeDie.curLoop = 0;
	life = 2;
	damaged = false;
	type = _type; // 1- spawn 2-follow and spawn
}

Hornet::Hornet()
{
}


Hornet::~Hornet()
{
}
