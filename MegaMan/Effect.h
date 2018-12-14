#pragma once
#include "DrawableObject.h"
#include "List.h"
#include "TileMap.h"
class Effect: public DrawableObject
{
	static List<Effect*>* instance;
public:
	static List<Effect*>* getInstance();
	void draw();
	void update();
	Effect();
	~Effect();
};

