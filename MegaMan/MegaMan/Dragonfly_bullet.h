#pragma once
#include"List.h"
#include"Rockman.h"
class Dragonfly_bullet:public MovableObject
{
	static List<Dragonfly_bullet*>*  dragonfly_bullet;
public:
	static  List<Dragonfly_bullet*>* getListDragonfly_bullet();

	GameTimeLoop timeDeath;

	void update();
	void draw();
	void onCollision(BaseObject* S, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	Dragonfly_bullet(int xDragonfly, int yDragonfly, Direction directionDragonfly);
	Dragonfly_bullet();
	~Dragonfly_bullet();
};

