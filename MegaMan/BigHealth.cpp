#include "BigHealth.h"
#include"Rockman.h"



void BigHealth::onAABBCheck(BaseObject * other)
{
	Item::onAABBCheck(other);
	if (other == ROCKMAN)
	{
		ROCKMAN->life += 8;
		if (ROCKMAN->life >= 24) ROCKMAN->life = 24;
		//audio
		AudioManager::getInstance()->Play(AUDIO_ROCK_PICKUP);
	}
}

BigHealth::BigHealth()
{
	sprite = SPRITEMANAGER->sprites[SPR_BIG_HEALTH];
	this->width = 16;
	this->height = 12;
}


BigHealth::~BigHealth()
{
}
