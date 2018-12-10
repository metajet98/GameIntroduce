#include "Genjibo.h"

Genjibo* Genjibo::instance = 0;
Genjibo * Genjibo::getInstance()
{
	if (instance == 0)
		instance = new Genjibo();
	return instance;
}

void Genjibo::draw()
{
	Enermy::draw();
}

void Genjibo::update()
{
	if (!ROCKMAN->onAreaBoss) return;
	if (!ROCKMAN->alive)
	{
		changeAction(GENJIBO_STAND);
		return;
	}
	if (damaged && alive)
	{
		setOnHit(false);
		damaged = false;
		changeAction(GENJIBO_MOVE);
		return;
	}
	if (alive)
	{
		timePerAnimation.curLoop++;
		if (timePerAnimation.curLoop >= 50)
		{
			if (life >= 9)
			{
				if (isOnGround)
				{
					changeAction(GENJIBO_MOVE);
					vx = 120 * direction;
					timeJump.canCreateFrame();
					if (timeJump.isTerminated())
					{
						vy = -260;
						isOnGround = false;
						timeJump.start();
					}
				}
				else
				{
					//vy += ay * TIME;
				}
			}
			else
			{
				if (isOnGround)
				{
					changeAction(GENJIBO_MOVE);
					vx = 100 * direction;
					timeJump.canCreateFrame();
					if (timeJump.isTerminated())
					{
						vy = -250;
						isOnGround = false;
						timeJump.start();
					}
				}
				else
				{
					vy += ay * TIME;
				}
			}
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
			curFrame = 0;
		}
		else sprite->animates[curAnimation].next(curFrame);
	}
}

void Genjibo::onCollision(BaseObject * other, int nx, int ny)
{
	MovableObject::onCollision(other, nx, ny);
	if (nx != 0 && other->collisionType == CT_GROUND)
	{
		direction = (Direction)nx;
		vx = direction * 120;
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
			setOnHit(true);
			other->allowDelete = true;
			//gameTimeLoop.start();
		}

		if (life <= 0)
		{
			this->alive = false;
			ROCKMAN->onAreaBoss = false;
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
	alive = true;
	life = 16;
	direction = Left;
	curAnimation = GENJIBO_MOVE;
	curFrame = 0;
	x = 4509;
	y = 350;
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
	life = 16;
	sprite = SPRITEMANAGER->sprites[SPR_GENJIBO];
	direction = Left;
	curFrame = 0;
	curAnimation = GENJIBO_STAND;
	onHit = false;
	damaged = false;
	damagedTime.init(0.2, 3);
	damagedTime.start();
	timePerAnimation.curLoop = 0;
	timeJump.init(0.2,5);
	timeJump.start();
	animation_delaytime = 0.1f;
	damage = 2;
	ay = GRAVITY;
	x = 4509;
	y = 350;
	width = 49;
	height = 49;
}


Genjibo::~Genjibo()
{
}
