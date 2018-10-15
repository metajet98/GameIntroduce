#include "Rockman.h"


Rockman* Rockman::instance = 0;
Rockman * Rockman::getInstance()
{

	if (instance == 0)
		instance = new Rockman();
	return instance;
}
void Rockman::onCollisionPush(BaseObject*S, int nx, int ny)
{
	float magnitude = sqrt(vx*vx + vy * vy) * COLLISION->remainingtime;
	float dotprod = vx * nx + vy * ny;
	if (dotprod > 0.0f)
	{
		dotprod = 1.0f;
	}
	else
	{
		dotprod = -1.0f;
	}
	//vx = dotprod * nx*magnitude;
	vy = dotprod * ny*magnitude;
	isPushing = true;
}
void Rockman::onCollision(BaseObject*S, int nx, int ny)
{
	if (isFalling&&!isOnGround)
		onCollisionPush(S, nx, ny);
	MovableObject::onCollision(S,nx,ny);
}

void Rockman::updateLocation()
{
	x += dx;
	y += dy;
}



void Rockman::draw()
{	
	int xInViewport, yInViewport;
	TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);

	if(curAnimation==JUMP)
		sprite->draw(xInViewport, yInViewport, curAnimation, ++curFrame*TIMEJUMP);
	else sprite->draw(xInViewport, yInViewport, curAnimation, (++curFrame)%CONTROLSPRITE->getCountFrame(curAnimation));
	//CONTROLSPRITE->draw(sprite, xInViewport, yInViewport, curAnimation,curFrame);
}

void Rockman::changeAction(int newAction)
{
	DrawableObject::changeAction(newAction);

	if (curAnimation != newAction)
	{
		curAnimation = newAction;
	}
}

void Rockman::update()
{

	updateDirection();
	updateChangeAnimation();
	MovableObject::update();
}

void Rockman::updateDirection()
{
	if (KEY->keyLeft)
		direction = Left;
	if (KEY->keyRight)
	{
		direction = Right;
	}
	if (KEY->keyMove)
	{
		vx = ROCKMAN_VX_GO * direction;
	}
	else
	{
		vx = 0;
	}
}

void Rockman::updateChangeAnimation()
{
	if (isOnGround)
	{
		if (KEY->keyJumpPress)
		{
			vy = -160;
			curFrame = 0;
			changeAction(JUMP);
			isFalling = true;
			
		}
		else
		{
			if (KEY->keyAttack)
				changeAction(SHOT);
			else
			{
					if (KEY->keySlide)
					{
						changeAction(SLIDING);
					}
					else
					{
						if (KEY->keyMove)
							changeAction(MOVE);
						else
						{
							changeAction(STAND);
						}
					}
				

			}
		}

	}
	//else isFalling = false;
}
Rockman::Rockman()
{
	sprite = SPRITEMANAGER->sprites[SPR_MAIN];
	x = 126;
	y = 674;
	width = 30;
	height = 38;
	isFalling = false;
}


Rockman::~Rockman()
{
}
