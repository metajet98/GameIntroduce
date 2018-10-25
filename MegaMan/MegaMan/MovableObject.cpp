#include "MovableObject.h"


void MovableObject::updateVerlocity()
{
	vy += ay * TIME;
	dx = vx * TIME;
	dy = vy * TIME;
}

void MovableObject::update()
{
	isOnGround = false;
	updateVerlocity();
	DrawableObject::update();
}

void MovableObject::draw()
{

	DrawableObject::draw();
}

void MovableObject::onCollision(BaseObject * other, int nx, int ny)
{
	if (other->collisionType == CT_GROUND)
	{
		if (ny == -1)
			isOnGround = true;

		if (ny != 0 || nx != 0)
			COLLISION->preventMove(this, other);

		if (ny < 0)
			vy = 0;
	}
}

MovableObject::MovableObject()
{
	direction = Right;
	ay = GRAVITY;
}

MovableObject::~MovableObject()
{
}