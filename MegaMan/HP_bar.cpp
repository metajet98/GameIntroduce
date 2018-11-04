#include "HP_bar.h"
#include<string>

HP_bar* HP_bar::instance = 0;
HP_bar * HP_bar::getInstance()
{
	if (instance == 0)
		instance = new HP_bar();
	return instance;
}

void HP_bar::draw()
{
	if (sprite == 0)
		return;

	int xInViewport, yInViewport;
	TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);
	
	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
}

void HP_bar::update()
{
	updateLocation();

	if (ROCKMAN->life > 0)
	{
		int healthPoint = ROCKMAN->life;
		if (healthPoint > curFrame)
		{
			curFrame++;
		}
		else 
		{
			curFrame = healthPoint; 
		}
	}
	else { curFrame = 0; }
}

void HP_bar::updateLocation()
{
	x += CAMERA->dx;
	y += CAMERA->dy;
}

HP_bar::HP_bar()
{
	sprite = SPRITEMANAGER->sprites[SPR_HP_BAR_MGM];
	sprite_BOSS = SPRITEMANAGER->sprites[SPR_HP_BAR_BOSS];
	curAnimation = 0;
	curFrame = 0;
	curFrame_Boss = 0;
	x = Map::curMap->xMap;
	y = Map::curMap->yMap;
	gameTimeLoop.init(0.2, 400);
	gameTimeLoop.start();
}


HP_bar::~HP_bar()
{
}
