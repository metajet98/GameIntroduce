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
	sprites[SPR_ROCK_DIE] = new Sprite("Data\\Rockman\\die.png", "Data\\Rockman\\die.txt");

	sprites[SPR_DRAGONFLY] = new Sprite("Data\\Enermies\\butterfly\\butterlift.png", "Data\\Enermies\\butterfly\\butterlift.txt");
	sprites[SPR_DRAGONFLY_BULLET] = new Sprite("Data\\Enermies\\butterfly\\butterlift.png", "Data\\Enermies\\butterfly\\butterfly_bullet.txt");

	sprites[SPR_NOTORBANGER] = new Sprite("Data\\Enermies\\notorbanger\\notorbanger.png", "Data\\Enermies\\notorbanger\\notorbanger.txt");
	sprites[SPR_NOTORBANGER_BULLET] = new Sprite("Data\\Enermies\\notorbanger\\notorbanger.png", "Data\\Enermies\\notorbanger\\notorbanger_bullet.txt");

	sprites[SPR_CATERKILLER] = new Sprite("Data\\Enermies\\caterkiller\\caterkiller.png", "Data\\Enermies\\caterkiller\\caterkiller.txt");
	sprites[SPR_CATERKILLER_BULLET] = new Sprite("Data\\Enermies\\caterkiller\\caterkiller.png", "Data\\Enermies\\caterkiller\\caterkiller_bullet.txt");

	sprites[SPR_ENEMY_DIE] = new Sprite("Data\\Miscellaneous\\x3_explosions.png", "Data\\Miscellaneous\\enemy_die.txt");
	sprites[SPR_BOSS_DIE] = new Sprite("Data\\Miscellaneous\\x3_explosions.png", "Data\\Miscellaneous\\boss_die.txt");
}


SpriteManager::~SpriteManager()
{
	for (int i = 0; i < SPR_COUNT; i++)
	{
		delete[] sprites[i]->animates;
		delete sprites[i];
	}
}
