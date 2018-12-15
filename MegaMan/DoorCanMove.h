#pragma once
#include "MovableObject.h"
#include "TileMap.h"
#include "Rockman.h"
#include "List.h"
class DoorCanMove:public MovableObject
{
	static List<DoorCanMove*>* instance;
	GameTimeLoop timeDeath;
public:
	static List<DoorCanMove*>* getInstance();

	void draw();
	void update();
	void onCollision(BaseObject*S, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	void restore(BaseObject* obj);
	DoorCanMove();
	DoorCanMove(int _x,int _y,int w,int h);
	~DoorCanMove();
};

