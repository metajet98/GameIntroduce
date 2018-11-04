#include "Caterkiller.h"

Caterkiller* Caterkiller::instance = 0;

Caterkiller * Caterkiller::getInstance()
{
	if (instance == 0)
		instance = new Caterkiller();
	return instance;
}

void Caterkiller::draw()
{
	Enermy::draw();
}

void Caterkiller::update()
{
	if (damaged)
	{
		gameTimeLoop.canCreateFrame();

		if (gameTimeLoop.isTerminated())
			damaged = false;

		return;
	}
	if (x<CAMERA->x || x>(CAMERA->x + CAMERA->width)) isMove = false;
	else isMove = true;
	if (!isMove && alive)
	{
		dy = 0;
		curAnimation = CATERKILLER_STAND;
		dx = direction;
	}
	else if (alive && isMove)
	{
		curAnimation = CATERKILLER_MOVE;
		vy = UpDown * 10;
		

		if (abs(ROCKMAN->x - x) <= 70)
		{
			curAnimation = CATERKILLER_SHOT;
			if (CATERKILLER_BULLET->Count < 2)
			{
				Caterkiller_bullet *cb1,*cb2;
				if (direction == Left)
				{
					
					cb1 = new Caterkiller_bullet(this->x + this->width - 16, this->y + 8, Left,true);
					cb2 = new Caterkiller_bullet(this->x + this->width - 16, this->y + this->height - 21, Right,false);
					cb2->curFrame = cb1->curFrame;
				}
				else
				{
					cb1 = new Caterkiller_bullet(this->x - 16, this->y + 8, Right,true);
					cb2 = new Caterkiller_bullet(this->x - 16, this->y + this->height - 8, Left,false);
				}
				CATERKILLER_BULLET->_Add(cb1);
				CATERKILLER_BULLET->_Add(cb2);
			}
		}
	}
	MovableObject::update();
}

void Caterkiller::onCollision(BaseObject * S, int nx, int ny)
{
	Enermy::onCollision(S,nx,ny);
	if (nx != 0 && S->collisionType == CT_GROUND)
	{
		if ((S->y + 5) >= y)
			UpDown = 1;
		if ((S->y + S->height) <= (y + height))
			UpDown = -1;
	}
}

void Caterkiller::restore(BaseObject * obj)
{
	alive = true;
	life = 2;
}

Caterkiller::Caterkiller()
{
	sprite = SPRITEMANAGER->sprites[SPR_CATERKILLER];
	ay = 0;
	direction = Left;
	vx = direction;
	UpDown = -1;
	curAnimation = CATERKILLER_STAND;
	curFrame = 0;
	life = 2;
	collisionType = CT_ENERMY;
	width = 40;
	height = 51;
}


Caterkiller::~Caterkiller()
{
}
