#pragma once
#include"Sprite.h"

enum SPRITE_OBJECT
{
	SPR_MAIN,
	SPR_COUNT,
};

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

