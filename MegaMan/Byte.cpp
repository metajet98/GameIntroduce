#include "Byte.h"


Byte* Byte::instance = 0;
Byte::Byte()
{
	alive = true;
	sprite = SPRITEMANAGER->sprites[SPR_BYTE];
	direction = Left;
	curAnimation = BYTE_STAND;
	curFrame = 0;
	damaged = false;
	damage = 2;
	allowDraw = true;
	life = LIFE_BYTE;
	damagedTime.init(0.01, 20);
	damagedTime.start();
	timePerAnimation.init(0.2, 10);
	timePerAnimation.start();
	timeShoot.curLoop = 0;
	timeMove.curLoop = 0;
	frameType = HEIGHT_84;
}


Byte::~Byte()
{
}

Byte * Byte::getInstance()
{
	if (instance == 0)
		instance = new Byte();
	return instance;
}

void Byte::draw()
{
	if (!allowDraw) return;
	if (!alive)
	{
		dx = 0;
		dy = 0;
		ay = 0;
		if (timeDeath.canCreateFrame())
		{
			sprite = SPRITEMANAGER->sprites[SPR_BOSS_DIE];
			curAnimation = 0;
			curFrame = (curFrame + 1) % 6;
			AudioManager::getInstance()->Play(AUDIO_BOSS_DIE);
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
		int deltaY = height - sprite->animates[curAnimation].frames[curFrame].height;
		TileMap::curMap->convertToViewportPos(x, y + deltaY, xInViewport, yInViewport);
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

void Byte::update()
{
	if (!ROCKMAN->onAreaBossSub) return;
	if (!ROCKMAN->alive)
	{
		changeAction(BYTE_STAND);
		return;
	}
	if (damaged && alive)
	{
		if (damagedTime.canCreateFrame())
			allowDraw = !allowDraw;
		if (damagedTime.isTerminated())
		{
			damaged = false;
			allowDraw = true;
			damagedTime.start();
		}
		return;
	}
	if (alive && isOnGround)
	{
		timePerAnimation.curLoop++;
		if (timePerAnimation.curLoop >= 50)
		{
			if (timePerAnimation.curLoop > 50 && timePerAnimation.curLoop < 100)
			{
				int delta = ROCKMAN->xCenter() - xCenter();
				if (ROCKMAN->right() < x)
					direction = Left;
				if (ROCKMAN->x > right()) direction = Right;
				changeAction(BYTE_SHOT);
				// bullet
				if(BYTE_BULLET->Count<1 && curFrame == 3 && curAnimation == BYTE_SHOT)
				{
					Byte_bullet* bb;
					if (direction == Left)
					{
						bb = new Byte_bullet(this->x, this->y, this->direction);
					}
					else
					{
						bb = new Byte_bullet(this->x + this->width, this->y, this->direction);
					}
					BYTE_BULLET->_Add(bb);
				}
			}
			else if (timePerAnimation.curLoop >= 100)
			{
				changeAction(BYTE_MOVE);
				vx += 10 * direction;
			}
		}
	}
	updateMove();
}

void Byte::updateMove()
{
	isOnGround = false;
	updateVerlocity();
	if (!alive) return;

	BaseObject::update();
	if (!pauseAnimation)
	{
		if (curAnimation == BYTE_STAND)
		{
			delayAnimation.minFrameTime = 5 * ANIMATE_DELAY_TIME_DEFAULT;
			delayAnimation.maxFrameTime = 6 * ANIMATE_DELAY_TIME_DEFAULT;
		}
		else
		{
			delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT;
			delayAnimation.maxFrameTime = 2 * ANIMATE_DELAY_TIME_DEFAULT;
			if (curAnimation == BYTE_ATT)
			{
				delayAnimation.minFrameTime = 0;
				delayAnimation.maxFrameTime = 0;
			}
			else
			{
				delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT;
				delayAnimation.maxFrameTime = 2 * ANIMATE_DELAY_TIME_DEFAULT;
			}
		}
		if (delayAnimation.canCreateFrame())
		{
			if (curFrame == sprite->animates[curAnimation].nFrame - 1)
			{
				if (curAnimation == BYTE_STAND && curFrame == sprite->animates[curAnimation].nFrame - 1)
				{
					curFrame = 0;
					return;
				}
				curFrame = sprite->animates[curAnimation].nFrame - 1;
			}
			else sprite->animates[curAnimation].next(curFrame);
		}
	}
}

void Byte::onLastFrameAnimation(BYTE_ACTION ba)
{
	
}

void Byte::updateHeight()
{
	/*switch (curAnimation)
	{
	case BYTE_STAND:
		height = 84;
		break;
	case BYTE_SHOT:case BYTE_MOVE:
		height = 74;
		if (frameType == HEIGHT_84)
		{
			y += 10;
			frameType = HEIGHT_74;
		}
		else if (frameType == HEIGHT_80)
		{
			y += 4;
			frameType = HEIGHT_80;
		}
	case BYTE_ATT:
		height = 80;
		if (curFrame != 10)
		{
			if (frameType == HEIGHT_84)
			{
				y -= 4;
				frameType = HEIGHT_84;
			}
			else if (frameType == HEIGHT_74)
			{
				y += 6;
				frameType = HEIGHT_74;
			}
		}
		else
		{
			height = 91;
			if (frameType == HEIGHT_84)
			{
				y += 7;
				frameType = HEIGHT_84;
			}
			else if (frameType == HEIGHT_74)
			{
				y += 17;
				frameType = HEIGHT_74;
			}
			else if (frameType == HEIGHT_80)
			{
				y += 11;
				frameType = HEIGHT_80;
			}
		}
	}*/

}

void Byte::onCollision(BaseObject * other, int nx, int ny)
{
	MovableObject::onCollision(other, nx, ny);
	if (nx != 0 && (other->collisionType == CT_GROUND || other->collisionType==CT_DOOR || other->collisionType==CT_DOOR_CAN_MOVE))
	{
		vx = 0;
		direction = direction == Left ? Right : Left;
		changeAction(BYTE_STAND);
		timePerAnimation.curLoop = 0;
		timeShoot.curLoop = 0;
		timeMove.curLoop = 0;
	}
}

void Byte::onAABBCheck(BaseObject * other)
{
	if (other == ROCKMAN)
	{
		if (!ROCKMAN->onHit && !ROCKMAN->invisible)
		{
			changeAction(BYTE_ATT);
			timePerAnimation.curLoop = 0;
			vx = 0;
			ROCKMAN->changeAction(ON_HIT);
			ROCKMAN->setOnHit(true);
			/*if (curAnimation == BYTE_ATT && curFrame == sprite->animates[curAnimation].nFrame - 1)
			{
				ROCKMAN->vx = direction * 500;

			}*/
			ROCKMAN->vx = direction * 300;
			ROCKMAN->life -= damage;
			ROCKMAN->gameTimeLoop.start();
		}
	}
	if (other->collisionType == CT_BUTLET)
	{
		RockButlet* r = (RockButlet*)other;
		if (!damaged)
		{
			damaged = true;
			if (r->categoryBullet == OF_STRONG_MEGAMAN)
				this->life -= 2;
			else if (r->categoryBullet == OF_STRONG_2_MEGAMAN)
			{
				this->life -= 3;
				dx = 0;
			}
			else this->life--;
			other->allowDelete = true;
			//gameTimeLoop.start();
		}

		if (life <= 0)
		{
			this->alive = false;
			ROCKMAN->onAreaBossSub = false;
			DoorCanMove::getInstance()->at(1)->alive = false;
		}
	}
}

void Byte::restore(BaseObject * obj)
{
	if (ROCKMAN->onAreaBoss) return;
	life = 18;
	alive = true;
	direction = Left;
	curAnimation = BYTE_STAND;
	curFrame = 0;
	// cap nhat lai x,y
	x = 927;
	y = 90;

}

void Byte::changeAction(int newAction)
{
	if (curAnimation != newAction)
	{
		curFrame = 0;
		curAnimation = newAction;
	}
}
