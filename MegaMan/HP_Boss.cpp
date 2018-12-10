#include "HP_Boss.h"


HP_Boss * HP_Boss::instance = 0;
HP_Boss * HP_Boss::getInstance()
{
	if (instance == 0)
		instance = new HP_Boss();
	return instance;
}

void HP_Boss::draw()
{
	if (sprite == 0) return;

	int xInViewport, yInViewport;
	TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);

	if (ROCKMAN->onAreaBoss && RHINO->alive)
	{
		sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
	}
}

void HP_Boss::update()
{
	/*if (ROCKMAN->onAreaBoss)
	{
		if (RHINO->life > 0)
		{
			int healthPoint1 = RHINO->life;
			if (healthPoint1 > curFrame)
			{
				curFrame++;
			}
			else
			{
				curFrame = healthPoint1;
			}
		}
		else { curFrame = 0; }
	}*/
}

void HP_Boss::updateLocation()
{
	x += CAMERA->dx;
	y += CAMERA->dy;
}

HP_Boss::HP_Boss()
{
	sprite = SPRITEMANAGER->sprites[SPR_HP_BAR_BOSS];
	curAnimation = 0;
	curFrame = RHINO->life;
	x = CAMERA->x + 220;
	y = CAMERA->y;
}


HP_Boss::~HP_Boss()
{
}
