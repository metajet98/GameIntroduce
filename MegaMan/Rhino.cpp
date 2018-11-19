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
			damagedTime.canCreateFrame();
			if (damagedTime.isTerminated())
			{
				setOnHit(false);
				damaged = false;
				if (life >= 12) changeAction(RA_MOVE);
				else changeAction(RA_SHOT);
				damagedTime.start();
			}

		return;
	}
	//update direction
	if (alive && isOnGround)
	{
		int delta = ROCKMAN->xCenter() - xCenter();
		//direction = delta < 0 ? Left : Right;
		if (ROCKMAN->right() < x)
			direction = Left;
		if (ROCKMAN->x > right()) direction = Right;

		/*curAnimation = randomAnimation();
		changeAction(curAnimation);

		switch (curAnimation)
		{
		case RA_MOVE:
			if (delta <= 10 && delta >= -10)
			{
				curAnimation = RA_ATT;
				changeAction(curAnimation);
			}
			else
			{
				vx = delta==0?0:direction * 50;
			}
			break;
		case RA_ATT:
			DrawableObject::update();
			break;
		default:
			dx = 0;
			curAnimation = RA_SHOT;
			changeAction(curAnimation);

			if (RHINO_BULLET->Count < 1 && curFrame == 5)
			{
				Rhino_bullet* rb;
				if (direction == Left)
				{
					rb = new Rhino_bullet(this->x, this->y, this->direction);
				}
				else rb = new Rhino_bullet(this->x + this->width, this->y, this->direction);
				RHINO_BULLET->_Add(rb);
			}

			break;
		}*/
		if (life >= 12)
		{
			changeAction(RA_MOVE);
			if (abs(delta) <= ROCKMAN->width/2 + this->width/2)
			{
				dx = 0;
				changeAction(RA_ATT);
				
			}
			else
			{
				changeAction(RA_MOVE);
				vx = direction * 50;
			}
		}
		else if (life < 12)
		{
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

	MovableObject::update();
}

void Rhino::onCollision(BaseObject * other, int nx, int ny)
{
	MovableObject::onCollision(other, nx, ny);
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
	curFrame = 0;
	life = 24;
	BlinkTime.init(0.01, 20);
	BlinkTime.start();
	direction = Left;
	appearHP = false;
	isBlink = false;
	allowDraw = true;
	width = 87;
	height = 45;
	onHit = false;
	damagedTime.init(0.2, 10);
	damagedTime.start();
	timePerAnimation.init(0.2, 4);
	timePerAnimation.start();
	damage = 2;
}


Rhino::~Rhino()
{
}