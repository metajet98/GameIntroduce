#pragma once
#include"Sprite.h"

class SpriteManager
{
private:
	static SpriteManager*instance;
public:
	static SpriteManager*getInstance();

	Sprite** sprites;
	/*Texture*enemies;
	Texture*bosses;*/

	SpriteManager();
	~SpriteManager();
};

