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
		damaged = false;
		return;
	}
	if (!alive)
	{
		dx = 0;
		dy = 0;
		ay = 0;
	}
	if (x<CAMERA->x || x>(CAMERA->x + CAMERA->width)) isMove = false;
	else isMove = true;
	if (!isMove && alive)
	{
		dy = 0;
		curAnimation = CATERKILLER_STAND;
		dx = direction;
		return;
	}
	else if (alive && isMove)
	{
		/*if (abs(this->oldY - this->y) > 30)
			UpDown = -1 * UpDown;*/
		curAnimation = CATERKILLER_MOVE;
		vy = UpDown * 10;
		

		if (abs(ROCKMAN->xCenter() - xCenter()) <= 70)
		{
			curAnimation = CATERKILLER_SHOT;
			if (curFrame == sprite->animates[CATERKILLER_SHOT].nFrame - 1)
			{
				if (CATERKILLER_BULLET->Count < 2)
				{
					Caterkiller_bullet *cb1, *cb2;
					if (direction == Left)
					{

						cb1 = new Caterkiller_bullet(this->x + this->width - 16, this->y + 8, Left, true);
						cb2 = new Caterkiller_bullet(this->x + this->width - 16, this->y + this->height - 21, Right, false);
						cb2->curFrame = cb1->curFrame;
					}
					else
					{
						cb1 = new Caterkiller_bullet(this->x - 16, this->y + 8, Right, true);
						cb2 = new Caterkiller_bullet(this->x - 16, this->y + this->height - 8, Left, false);
						cb2->curFrame = cb1->curFrame;
					}
					CATERKILLER_BULLET->_Add(cb1);
					CATERKILLER_BULLET->_Add(cb2);
				}
				curFrame = 0;
			}
		}
	}
	MovableObject::update();
}

void Caterkiller::onCollision(BaseObject * S, int nx, int ny)
{
	Enermy::onCollision(S,nx,ny);
	if (ny != 0) UpDown = -1 * UpDown;
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

Caterkiller::Caterkiller(int _direction)
{
	sprite = SPRITEMANAGER->sprites[SPR_CATERKILLER];
	ay = 0;
	direction = (_direction == -1) ? Left : Right;
	vx = direction;
	UpDown = -1;
	curAnimation = CATERKILLER_STAND;
	curFrame = 0;
	life = 2;
	collisionType = CT_ENERMY;
	width = 40;
	height = 51;
}

Caterkiller::Caterkiller()
{
	sprite = SPRITEMANAGER->sprites[SPR_CATERKILLER];
	ay = 0;
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
