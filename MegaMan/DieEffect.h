#pragma once
#include"TileMap.h"
#include"List.h"
#include"MovableObject.h"
enum AFFECT_CATEGORY {
	ROCK_DIE,
	BOSS_DIE
};
class DieEffect: public MovableObject
{
	static List<DieEffect*>* list;
public:
	static List<DieEffect*>* getList();
	void draw();
	void update();
	DieEffect(AFFECT_CATEGORY);
	DieEffect();
	~DieEffect();
};

