#pragma once
#include"MovableObject.h"
#include"Constant.h"
#include"TileMap.h"
#include"Rockman.h"
#include"RockButlet.h"

class Enermy:public MovableObject
{
public:
	CATEGORY_ENEMY categoryEnermy;
	int count;
	int damage;
	bool damaged;
	GameTimeLoop timeDeath;

	virtual void update();
	virtual void draw();
	virtual void onCollision(BaseObject* other, int nx, int ny);
	virtual void onAABBCheck(BaseObject* other);
	virtual void restore(BaseObject* obj);

	Enermy();
	~Enermy();
};

