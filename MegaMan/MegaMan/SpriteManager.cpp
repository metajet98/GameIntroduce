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
	sprites = new Sprite*[1];
	sprites[SPR_MAIN] = new Sprite("Data\\Rockman\\rock_x3.png", "Data\\Rockman\\rockman.txt");
	
}


SpriteManager::~SpriteManager()
{
	delete sprites[0]->image;
	delete sprites[0]->animates;
	delete sprites[0];

	delete sprites[2]->image;
	delete sprites[2]->animates;
	delete sprites[2];
}
