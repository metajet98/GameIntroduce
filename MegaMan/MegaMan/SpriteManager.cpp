#include "SpriteManager.h"


SpriteManager*SpriteManager::instance = 0;

SpriteManager * SpriteManager::getInstance()
{
	if (instance == 0)
		instance = new SpriteManager();
	return instance;
}

SpriteManager::SpriteManager()
{
	sprites = new Sprite*[SPR_COUNT];
	sprites[SPR_MAIN] = new Sprite("Data\\Rockman\\rock_x3.png", "Data\\Rockman\\rockman.txt");
	sprites[SPR_BUTLET] = new Sprite("Data\\Rockman\\butlet.png", "Data\\Rockman\\butlet.txt");

	sprites[SPR_DRAGONFLY] = new Sprite("Data\\Enermies\\butterfly\\butterlift.png", "Data\\Enermies\\butterfly\\butterlift.txt");
	sprites[SPR_DRAGONFLY_BULLET] = new Sprite("Data\\Enermies\\butterfly\\butterlift.png", "Data\\Enermies\\butterfly\\butterfly_bullet.txt");

	sprites[SPR_NOTORBANGER] = new Sprite("Data\\Enermies\\notorbanger\\notorbanger.png", "Data\\Enermies\\notorbanger\\notorbanger.txt");
	sprites[SPR_NOTORBANGER_BULLET] = new Sprite("Data\\Enermies\\notorbanger\\notorbanger.png", "Data\\Enermies\\notorbanger\\notorbanger_bullet.txt");
}


SpriteManager::~SpriteManager()
{
	for (int i = 0; i < SPR_COUNT; i++)
	{
		delete[] sprites[i]->animates;
		delete sprites[i];
	}
}
