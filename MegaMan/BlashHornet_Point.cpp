#include "BlashHornet_Point.h"

List<BlashHornet_Point*>* BlashHornet_Point::instance = 0;
List<BlashHornet_Point*>* BlashHornet_Point::getInstance()
{
	if (instance == 0) instance = new List<BlashHornet_Point*>();
	return instance;
}

void BlashHornet_Point::draw()
{
	if (!alive)
	{
		BlashHornet_Point::getInstance()->_Remove(this);
		ROCKMAN->isFollowing = false;
		return;
	}

	if (sprite == 0)
		return;

	int xInViewport, yInViewport;
	TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);

	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
}

void BlashHornet_Point::update()
{
	timeDie.curLoop++;
	if (timeDie.curLoop >= 300)
	{
		alive = false;
		ROCKMAN->isFollowing = false;
	}
	
	if (isCollision)
	{
		x = ROCKMAN->x+2;
		y = ROCKMAN->y+2;
		vx = ROCKMAN->vx;
		vy = ROCKMAN->vy;
	}
	else
	{
		vx = ROCKMAN->x - this->x + direction*10;
		vy = ROCKMAN->y - this->y + direction* 10;
	}
	updateLocation();
	MovableObject::update();
}

void BlashHornet_Point::onCollision(BaseObject * other, int nx, int ny)
{
	if (other->collisionType == CT_PLAYER)
	{
		isCollision = true;
	}
}

BlashHornet_Point::BlashHornet_Point(int xBoss, int yBoss, Direction dir)
{
	sprite = SPRITEMANAGER->sprites[SPR_BLASHHORNET_POINT];
	curFrame = 0;
	curAnimation = 0;
	alive = true;
	x = xBoss;
	y = yBoss;
	direction = dir;
	timeDie.curLoop = 0;
	BlashHornet_Point::getInstance()->_Add(this);
	ay = 0;
	collisionType = CT_FOLLOWING;
}

BlashHornet_Point::BlashHornet_Point()
{
}


BlashHornet_Point::~BlashHornet_Point()
{
}
