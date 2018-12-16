#include "Genjibo.h"
#include "Scene.h"
#include "MainMenu.h"

Genjibo* Genjibo::instance = 0;
bool Genjibo::updating = false;
Genjibo * Genjibo::getInstance()
{
	if (instance == 0)
		instance = new Genjibo();
	return instance;
}

void Genjibo::draw()
{
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
		}

		if (timeDeath.isTerminated())
		{
			return;
		}

		int xInViewport, yInViewport;
		TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);
		sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
		return;
	}
	if (alive)
	{
		int deltaX = width - sprite->animates[curAnimation].frames[curFrame].width;
		int deltaY = height - sprite->animates[curAnimation].frames[curFrame].height;
		int xInViewport, yInViewport;
		TileMap::curMap->convertToViewportPos(x + deltaX / 2, y + deltaY / 2, xInViewport, yInViewport);
		int trucQuay = xInViewport + width / 2;

		if (direction != sprite->image->direction && curAnimation!= GENJIBO_ROLATE)
		{
			D3DXMATRIX mt;
			D3DXMatrixIdentity(&mt);
			mt._41 = 2 * trucQuay;
			mt._11 = -1;
			GRAPHICS->GetSprite()->SetTransform(&mt);
		}

		sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);

		if (direction != sprite->image->direction && curAnimation != GENJIBO_ROLATE)
		{
			D3DXMATRIX mt;
			D3DXMatrixIdentity(&mt);
			GRAPHICS->GetSprite()->SetTransform(&mt);
		}
	}
}

void Genjibo::update()
{
	if (!updating) return;
	//if (!ROCKMAN->onAreaBossSub) return;
	if (!ROCKMAN->alive)
	{
		changeAction(GENJIBO_STAND);
		return;
	}
	if (damaged && alive)
	{
		setOnHit(false);
		damaged = false;
		if(countJump<3)
			changeAction(GENJIBO_MOVE);
		else  if (countJump<6) changeAction(GENJIBO_ROLATE);
		else changeAction(GENJIBO_STAND);
		return;
	}
	//mech();
	if (alive)
	{
		// co animation appear can lam` appear xong run mech()
		if (appear)
		{
			changeAction(GENJIBO_APPEAR);
			if (curFrame == sprite->animates[curAnimation].nFrame - 1)
			{
				appear = false;
			}
			ROCKMAN->pauseAnimation = appear;
			ROCKMAN->dx = 0;
			ROCKMAN->dy = 1;
		}
		else
		{
			mech();
		}
	}
	updateMove();
}

void Genjibo::updateMove()
{
	if (!alive) return;
	//isOnGround = false;
	updateVerlocity();
	BaseObject::update();
	if (!pauseAnimation)
	{
		if (curFrame == sprite->animates[curAnimation].nFrame - 1)
		{
			if (curAnimation == GENJIBO_APPEAR)
				curFrame = sprite->animates[curAnimation].nFrame - 1;
			else curFrame = 0;
		}
		else sprite->animates[curAnimation].next(curFrame);
	}
}

void Genjibo::mech()
{
	if (countJump < 3)
	{
		ay = GRAVITY;
		timePerAnimation.curLoop++;
		if (timePerAnimation.curLoop >= 30)
		{
			if (isOnGround)
			{
				changeAction(GENJIBO_MOVE);
				vx = 120 * direction;
				if (x<=380)
				{
					vy = -260;
					isOnGround = false;
					timeJump.start();
				}
			}
		}
	}
	else if(countJump < 6)
	{
		ay = GRAVITY;
		timeJump.init(0.2, 3);
		timePerAnimation.curLoop++;
		if (timePerAnimation.curLoop >= 40)
		{
			if (isOnGround)
			{
				changeAction(GENJIBO_ROLATE);
				vx = 80 * direction;
				timeJump.canCreateFrame();
				if (timeJump.isTerminated())
				{
					vy = -200;
					isOnGround = false;
					timeJump.start();
				}
			}
		}
	}
	else
	{
		if (isOnGround)
		{
			timePerAnimation.curLoop++;
			if (timePerAnimation.curLoop >= 80)
			{
				changeAction(GENJIBO_STAND);
				ay = 0;
				//run around
				vx = direction*100;
				if (vy > 0 && y >= 375)
				{
					vx = 120 * direction;
					countJump = 0;
				}
			}
		}
	}
}
void Genjibo::onLastFrameAnimation(GENJIBO_ACTION ga)
{

}

void Genjibo::onCollision(BaseObject * other, int nx, int ny)
{
	MovableObject::onCollision(other, nx, ny);
	if (nx != 0 && (other->collisionType == CT_GROUND || other->collisionType == CT_DOOR || other->collisionType == CT_DOOR_CAN_MOVE) && curAnimation!=GENJIBO_STAND)
	{
		if(curAnimation!= GENJIBO_STAND)
			direction = (Direction)nx;
		if(curAnimation != GENJIBO_ROLATE)
			vx = direction * 120;
		else vx = direction * 80;
		//if (curAnimation == GENJIBO_STAND) vx = 0;
		//canMoveOnWall = true;
		//upDown = direction == Left ? Right : Left;
		
		timeJump.curLoop=0;
	}
	if (nx == -1 && (other->collisionType == CT_GROUND || other->collisionType == CT_DOOR || other->collisionType == CT_DOOR_CAN_MOVE) && curAnimation != GENJIBO_STAND)
	{
		if(countJump<7)
			countJump++;
		if(curAnimation!=GENJIBO_ROLATE)
			vx = 0;
		if (curAnimation != GENJIBO_ROLATE && countJump == 3)
		{
			timePerAnimation.curLoop = 0;
		}
		if (curAnimation == GENJIBO_ROLATE && countJump >= 6)
		{
			vx = 0;
			timePerAnimation.curLoop = 0;
		}
		/*if (curAnimation == GENJIBO_STAND)
			direction = Right;*/
	}
	
	/*if (ny == 1 && (other->collisionType == CT_GROUND || other->collisionType == CT_DOOR || other->collisionType == CT_DOOR_CAN_MOVE))
	{
		direction = upDown;
	}*/

	if ((other->collisionType == CT_GROUND || other->collisionType == CT_DOOR || other->collisionType == CT_DOOR_CAN_MOVE) && curAnimation == GENJIBO_STAND)
	{
		if (nx == 1 && upDown == Right)
		{
			vx = 0;
			upDown = Left;
			vy = upDown * 100;
		}
		else if (nx == -1 && upDown == Left)
		{
			vx = 0;
			upDown = Right;
			vy = upDown * 100;
		}
		if (ny == 1)
		{
			direction = Right;
		}
		else if (ny == -1)
		{
			direction = Left;
		}
	}
}

void Genjibo::onAABBCheck(BaseObject * other)
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
		RockButlet* r = (RockButlet*)other;
		if (!damaged && !appear)
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
			setOnHit(true);
			other->allowDelete = true;
			//gameTimeLoop.start();
		}

		if (life <= 0)
		{
			this->alive = false;
			DoorCanMove::getInstance()->at(0)->alive = false;
			ROCKMAN->onAreaBossSub = false;
		}
	}
}

void Genjibo::setOnHit(bool newOnHit)
{
	if (newOnHit)
	{
		changeAction(GENJIBO_DAMAGED);
	}

	onHit = newOnHit;
}

void Genjibo::restore(BaseObject * obj)
{
	if (ROCKMAN->onAreaBossSub) return;
	alive = true;
	life = LIFE_GENJIBO;
	direction = Left;
	curAnimation = GENJIBO_APPEAR;
	curFrame = 0;
	/*x = 4509;
	y = 350;*/
	x = 417;
	y = 380;
	damagedTime.start();
	timePerAnimation.curLoop = 0;
	timeJump.curLoop = 0;
	countJump = 0;
	updating = false;
	appear = true;
	vx = 0;
	vy = 0;
}

void Genjibo::changeAction(int newAction)
{
	if (curAnimation != newAction)
	{
		curFrame = 0;
		curAnimation = newAction;
	}
}
Genjibo::Genjibo()
{
	alive = true;
	life = LIFE_GENJIBO;
	sprite = SPRITEMANAGER->sprites[SPR_GENJIBO];
	direction = Left;
	upDown = Right;
	curFrame = 0;
	curAnimation = GENJIBO_APPEAR;
	onHit = false;
	damaged = false;
	damagedTime.init(0.2, 3);
	damagedTime.start();
	timePerAnimation.curLoop = 0;
	timeJump.init(0.2, 5);
	timeJump.start();
	animation_delaytime = 0.1f;
	damage = 2;
	ay = GRAVITY;
	/*x = 4509;
	y = 350;*/
	x = 417;
	y = 380;
	width = 49;
	height = 49;
	appear = true;
	countJump = 0;
	countAround = 0;
}


Genjibo::~Genjibo()
{
}
