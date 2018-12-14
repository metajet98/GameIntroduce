#include "NotorBanger.h"
#include<ctime>

NotorBanger* NotorBanger::instance = 0;
NotorBanger * NotorBanger::getInstance()
{
	if (instance == 0)
		instance = new NotorBanger();
	return instance;
}

void NotorBanger::draw()
{
	Enermy::draw();
}

void NotorBanger::update()
{
	if (damaged)
	{
		damaged = false;

		return;
	}
	
	if (alive)
	{
		// Use count jump to change direction

		if (isOnGround)
		{
			vx = 0;
			curAnimation = NOTORBANGER_STAND;
			timeStand.canCreateFrame();
			if (timeStand.isTerminated() && curAnimation != NOTORBANGER_JUMP)
			{
				if (countJump >= 3)
				{
					direction = direction == Left ? Right : Left;
					countJump = 0;
				}
				vx = direction * 50;
				vy = -120;
				curAnimation = NOTORBANGER_JUMP;
				countJump++;
				timeStand.start();
			}
		}
		
		if (abs(x - (ROCKMAN->x + ROCKMAN->width) <= 50) && curAnimation!=NOTORBANGER_JUMP)
		{
			if (ROCKMAN->x >= x + width)
			{
				direction = Right;
			}

			if (ROCKMAN->x <= x)
			{
				direction = Left;
			}
			curAnimation = NOTORBANGER_SHOT;
			vx = 0;
			vy = 0;
			timeShot.canCreateFrame();
			if (timeShot.isTerminated())
			{
				if (NOTOBANGER_BULLET->Count < 1)
				{
					NotoBanger_bullet* nb;
					if (direction == Left)
						nb = new NotoBanger_bullet(this->x, this->y, this->direction);
					else nb = new NotoBanger_bullet(this->x + this->width, this->y, this->direction);
					NOTOBANGER_BULLET->_Add(nb);
				}
				timeShot.start();
			}
			countJump = 0;
		}
		//isOnGround = false;
		MovableObject::update();
		
	}
	
}

void NotorBanger::onCollision(BaseObject * S, int nx, int ny)
{
	if (ny == 1) isOnGround = true;
	Enermy::onCollision(S, nx, ny);
	if (S->collisionType == CT_GROUND && nx != 0)
	{
		direction = (Direction)nx;
		countJump = 0;
	}
	/*if (right() >= S->right()-50 && nx == 0 && S->collisionType == CT_GROUND)
	{
		changeDirection = false;
		direction = Left;
	}

	if (S->collisionType == CT_GROUND && right() <= S->right() - 100 && left() >= S->left() + 100 && nx == 0)
		changeDirection = true;

	if (left() <= S->left()-50 && nx == 0)
	{
		direction = Right;
		changeDirection = false;
	}*/

}

void NotorBanger::restore(BaseObject * obj)
{
	Enermy::restore(obj);
	life = 3;
}

NotorBanger::NotorBanger()
{
	alive = true;
	sprite = SPRITEMANAGER->sprites[SPR_NOTORBANGER];
	direction = Left;
	curAnimation = NOTORBANGER_STAND;
	activity = NOTORBANGER_STAND;
	curFrame = 0;
	life = 3;
	width = 40;
	height = 25;
	collisionType = CT_ENERMY;
	timeStand.init(0.2, 10);
	timeStand.start();
	ay = GRAVITY;
	countJump = 0;
	//vy = 0;
	timeShot.init(0.2, 5);
	timeShot.start();
}


NotorBanger::~NotorBanger()
{
}
