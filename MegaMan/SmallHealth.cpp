#include "SmallHealth.h"



void SmallHealth::onAABBCheck(BaseObject * other)
{
	Item::onAABBCheck(other);
	if (other == ROCKMAN)
	{
		ROCKMAN->life += 4;
		if (ROCKMAN->life >= 24) ROCKMAN->life = 24;
		//audio
		AudioManager::getInstance()->Play(AUDIO_ROCK_PICKUP);
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
