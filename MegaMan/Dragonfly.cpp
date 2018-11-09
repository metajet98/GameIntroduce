#include "Dragonfly.h"


Dragonfly* Dragonfly::instance = 0;

Dragonfly * Dragonfly::getInstance()
{
	if (instance == 0)
		instance = new Dragonfly();
	return instance;
}



void Dragonfly::draw()
{
	Enermy::draw();
}

void Dragonfly::update()
{
	if (damaged)
	{
		/*gameTimeLoop.canCreateFrame();

		if (gameTimeLoop.isTerminated())
			damaged = false;*/
		damaged = false;
		return;
	}
	if (alive)
	{
		vx = direction * 40;
		if (direction == Left && abs((ROCKMAN->x + ROCKMAN->width) - x) < 20 && abs((y + height) - ROCKMAN->y) < 20)
		{
			vx = 0;
			curAnimation = DRAGONFLY_SHOT;
			if (curFrame == sprite->animates[DRAGONFLY_SHOT].nFrame - 1)
			{
				if (DRAGONFLY_BULLET->Count < 1)
				{
					Dragonfly_bullet *db = new Dragonfly_bullet(this->x, this->y, this->direction);
					DRAGONFLY_BULLET->_Add(db);
				}
			}
		}
		else curAnimation = DRAGONFLY_FLY;
		dx = vx * TIME;
	}

	MovableObject::update();
}

void Dragonfly::onCollision(BaseObject * S, int nx, int ny)
{
	Enermy::onCollision(S, nx, ny);
	if (S->collisionType == CT_GROUND && (nx != 0))
	{
		direction = (Direction)nx;
	}
	//if (S->collisionType == CT_BUTLET)
	//{
	//	life-=5;
	//	if (life <= 0) this->alive = false;
	//	S->allowDelete = true;
	//}
}

void Dragonfly::restore(BaseObject * obj)
{
	Enermy::restore(obj);
	life = 2;
}

Dragonfly::Dragonfly()
{
	sprite = SPRITEMANAGER->sprites[SPR_DRAGONFLY];
	direction = Right;
	curAnimation = DRAGONFLY_FLY;
	curFrame = 0;
	width = 42;
	height = 26;
	/*x = 445;
	y = 371;*/
	life = 2;
	x = 74;
	y = 535;
	vy = 0;
	ay = 0;
	//gameTimeLoopBullet = new GameTimeLoop();
	//gameTimeLoopBullet->init(0.7, 1);
	//gameTimeLoopBullet->start();
	collisionType == CT_ENERMY;
	timeShot.init(0.2, 10);
	timeShot.start();
}


Dragonfly::~Dragonfly()
{
}
