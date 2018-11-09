#include "DeadLane.h"


DeadLane * DeadLane::instance = 0;
DeadLane * DeadLane::getInstance()
{
	if (instance == 0)
		instance = new DeadLane();
	return instance;
}

void DeadLane::onAABBCheck(BaseObject * other)
{
	
}

void DeadLane::onCollision(BaseObject * other, int nx, int ny)
{
	if (other == ROCKMAN)
	{
		if (!ROCKMAN->onHit && !ROCKMAN->invisible)
		{
			ROCKMAN->changeAction(ON_HIT);
			ROCKMAN->setOnHit(true);
			ROCKMAN->life = 0;;
			ROCKMAN->gameTimeLoop.start();
		}
	}
}

DeadLane::DeadLane()
{
	this->collisionType = CT_DEAD_LANE;
}


DeadLane::~DeadLane()
{
}
