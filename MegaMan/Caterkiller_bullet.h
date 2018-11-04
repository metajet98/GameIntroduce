#pragma once
#include"MovableObject.h"
#include"List.h"
#include"TileMap.h"
#include"Rockman.h"
class Caterkiller_bullet:public MovableObject
{
	static List<Caterkiller_bullet*>* caterkiller_bullet;
public:
	static List<Caterkiller_bullet*>* getListCaterkiller_bullet();
	bool above;
	GameTimeLoop timeShot;

	void update();
	void draw();
	void onCollision(BaseObject* S, int nx, int ny);
	void onAABBCheck(BaseObject* other);

	Caterkiller_bullet(int xCater, int yCater, Direction directionCater,bool _above);
	Caterkiller_bullet();
	~Caterkiller_bullet();
};

