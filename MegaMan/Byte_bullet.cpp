#include "Byte_bullet.h"


List<Byte_bullet*>* Byte_bullet::instance = 0;
List<Byte_bullet*>* Byte_bullet::getInstance()
{
	if (instance == 0)
		instance = new List< Byte_bullet*>();
	return instance;
}

void Byte_bullet::update()
{
	vx = direction * 120;
	dx = vx * TIME;
	updateFrame();
}

void Byte_bullet::updateFrame()
{
	if (!alive) return;

	BaseObject::update();
	if (!pauseAnimation)
	{
		if (delayAnimation.canCreateFrame())
		{
			if (curFrame == sprite->animates[curAnimation].nFrame - 1)
			{
				if (curAnimation == 1)
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

void Byte_bullet::draw()
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
}

void Byte_bullet::onCollision(BaseObject * S, int nx, int ny)
{
	
}

void Byte_bullet::onAABBCheck(BaseObject * other)
{
	if (other == ROCKMAN && !ROCKMAN->onHit && !ROCKMAN->invisible)
	{
		ROCKMAN->changeAction(ON_HIT);
		ROCKMAN->setOnHit(true);
		ROCKMAN->life -= 1;
		this->allowDelete = true;
		ROCKMAN->gameTimeLoop.start();
	}
}

Byte_bullet::Byte_bullet()
{
}

Byte_bullet::Byte_bullet(int xByte, int yByte, Direction dir)
{
	sprite = SPRITEMANAGER->sprites[SPR_BYTE_BULLET];
	direction = dir;
	curAnimation = 0;
	curFrame = 0;
	collisionType = CT_BULLET_ENERMY;
	delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 2;
	delayAnimation.maxFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 3;
	vy = 0;
	ay = 0;
	x = xByte;
	y = yByte + 22;
}


Byte_bullet::~Byte_bullet()
{
}
