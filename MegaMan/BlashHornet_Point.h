#pragma once
#include "MovableObject.h"
#include "TileMap.h"
#include "List.h"
class BlashHornet_Point:public MovableObject
{
	static List<BlashHornet_Point*>* instance;
public:
	static List<BlashHornet_Point*>* getInstance();

	GameTimeLoop timeDie;
	bool isCollision;

	void draw();
	void update();
	void onCollision(BaseObject* other, int nx, int ny);
	BlashHornet_Point(int xBoss,int yBoss,Direction dir);
	BlashHornet_Point();
	~BlashHornet_Point();
};

