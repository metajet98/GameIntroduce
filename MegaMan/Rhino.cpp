#include "Rhino.h"
Rhino* Rhino::instance = 0;
Rhino * Rhino::getInstance()
{
	if (instance == 0)
		instance = new Rhino();
	return instance;
}


void Rhino::draw()
{
	if (!allowDraw) return;
	Enermy::draw();
}

void Rhino::update()
{
	if (!ROCKMAN->onAreaBoss) return;
	if (!ROCKMAN->alive)
	{
		changeAction(RA_STAND);
		return;
	}
	if (!alive)
	{

	}
	if (damaged && alive)
	{
		if (damagedTime.canCreateFrame())
			allowDraw = !allowDraw;
		if (damagedTime.isTerminated())
		{
			setOnHit(false);
			damaged = false;
			if (life >= 12) changeAction(RA_MOVE);
			else changeAction(RA_SHOT);
			allowDraw = true;
			damagedTime.start();
		}

		return;
	}
	//update direction
	//if (alive && isOnGround)
	//{
	//	int delta = ROCKMAN->xCenter() - xCenter();
	//	//direction = delta < 0 ? Left : Right;
	//	if (ROCKMAN->right() < x)
	//		direction = Left;
	//	if (ROCKMAN->x > right()) direction = Right;


	//	if (life >= 12)
	//	{
	//		changeAction(RA_MOVE);
	//		if (abs(delta) <= ROCKMAN->width / 2 + this->width / 2)
	//		{
	//			dx = 0;
	//			changeAction(RA_ATT);
	//		}
	//		else
	//		{
	//			changeAction(RA_MOVE);
	//			vx = direction * 50;
	//		}
	//	}
	//	else if (life < 12)
	//	{
	//		changeAction(RA_SHOT);
	//		dx = 0;
	//		if (RHINO_BULLET->Count < 1)
	//		{
	//			Rhino_bullet* rb;
	//			if (direction == Left)
	//			{
	//				rb = new Rhino_bullet(this->x, this->y, this->direction);
	//			}
	//			else rb = new Rhino_bullet(this->x + this->width, this->y, this->direction);
	//			RHINO_BULLET->_Add(rb);
	//		}
	//	}
	//}
	//mech 2
	if (alive && isOnGround)
	{
		timePerAnimation.curLoop++;
		if (life >= 18)
		{
			changeAction(RA_STAND);
			if (timePerAnimation.curLoop >= 50)
			{
				vx += 7 * direction;
				changeAction(RA_MOVE);
			}
		}
		else if (life < 18 && life>9)
		{
			//changeAction(RA_STAND);
			if (timePerAnimation.curLoop >= 50)
			{
				int delta = ROCKMAN->xCenter() - xCenter();
				vx += 7 * direction;
				changeAction(RA_MOVE);
				if (abs(delta) <= ROCKMAN->width / 2 + this->width / 2)
				{
					dx = 0;
					changeAction(RA_ATT);
				}
				if (abs(vx) >= 200)
				{
					vx = 0;
					direction = direction == Left ? Right : Left;
					timePerAnimation.curLoop = 0;
				}
			}
		}
		else if (life <= 9)
		{
			int delta = ROCKMAN->xCenter() - xCenter();
			if (ROCKMAN->right() < x)
				direction = Left;
			if (ROCKMAN->x > right()) direction = Right;
			changeAction(RA_SHOT);
			dx = 0;
			if (RHINO_BULLET->Count < 1)
			{
				Rhino_bullet* rb;
				if (direction == Left)
				{
					rb = new Rhino_bullet(this->x, this->y, this->direction);
				}
				else rb = new Rhino_bullet(this->x + this->width, this->y, this->direction);
				RHINO_BULLET->_Add(rb);
			}
		}
	}
	updateMove();
}

void Rhino::updateMove()
{
	isOnGround = false;
	updateVerlocity();
	if (!alive) return;

	BaseObject::update();
	if (!pauseAnimation)
	{
		if (curAnimation == RA_ATT || curAnimation == RA_STAND)
		{
			delayAnimation.minFrameTime = 4 * animation_dalaytime;
			delayAnimation.maxFrameTime = 5 * animation_dalaytime;
		}
		else
		{
			delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT;
			delayAnimation.maxFrameTime = 2 * ANIMATE_DELAY_TIME_DEFAULT;
		}
		if (delayAnimation.canCreateFrame())
		{
			if (curFrame == sprite->animates[curAnimation].nFrame - 1)
			{
				if (curAnimation == RA_ATT)
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

void Rhino::onCollision(BaseObject * other, int nx, int ny)
{
	MovableObject::onCollision(other, nx, ny);
	if (nx != 0 && other->collisionType == CT_GROUND && life > 9)
	{
		vx = 0;
		direction = direction == Left ? Right : Left;
		timePerAnimation.curLoop = 0;
	}
}
void Rhino::onAABBCheck(BaseObject * other)
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
				setOnHit(true);
			}
			else this->life--;
			HP_BOSS->curFrame = (life < 0) ? 0 : life;
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
void Rhino::setOnHit(bool newOnHit)
{
	if (newOnHit)
	{
		changeAction(RA_IsDAMAGED);
		vx = 0;
		vy = 0;
	}

	onHit = newOnHit;
}


void Rhino::die()
{
}

void Rhino::restore(BaseObject * obj)
{
	alive = true;
	x = 4509;
	y = 340;
	curAnimation = RA_STAND;
	curFrame = 0;
	life = 24;
	HP_BOSS->curAnimation = 0;
	HP_BOSS->curFrame = life;
}
void Rhino::changeAction(int newAction)
{
	if (curAnimation != newAction)
	{
		curFrame = 0;
		curAnimation = newAction;
	}
}
RHINO_ACTION Rhino::randomAnimation()
{
	srand(time(NULL));
	int result = rand() % 100;
	if (result >= 0 && result <= 20)
		return RA_ATT;
	if (result > 20 && result <= 80)
		return RA_MOVE;
	else
		return RA_SHOT;
}
Rhino::Rhino()
{
	alive = true;
	sprite = SPRITEMANAGER->sprites[SPR_RHINO];
	curAnimation = RA_STAND;
	animation_dalaytime = 0.2f;
	curFrame = 0;
	life = 24;
	direction = Left;
	appearHP = false;
	invisible = false;
	allowDraw = true;
	width = 87;
	height = 45;
	onHit = false;
	damagedTime.init(0.01, 30);
	damagedTime.start();
	timePerAnimation.init(0.2, 10);
	timePerAnimation.start();
	damage = 2;
}


Rhino::~Rhino()
{
}