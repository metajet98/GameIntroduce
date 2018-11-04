#include "SmallHealth.h"



void SmallHealth::onAABBCheck(BaseObject * other)
{
	Item::onAABBCheck(other);
	if (other == ROCKMAN)
	{
		ROCKMAN->life += 4;
		if (ROCKMAN->life >= 23) ROCKMAN->life = 23;
		//audio
	}
}

SmallHealth::SmallHealth()
{
	sprite = SPRITEMANAGER->sprites[SPR_SMALL_HEALTH];
	this->width = 10;
	this->height = 8;

}


SmallHealth::~SmallHealth()
{
}