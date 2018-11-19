#pragma once
#include"MovableObject.h"
#include"List.h"
#include"TileMap.h"
class Rhino_bullet:public MovableObject
{
	static List<Rhino_bullet*>* rhinobullet;
public:
	static List<Rhino_bullet*>* getListBossBullet();

	void update();
	void draw();
	void onCollision(BaseObject* S, int nx, int ny);
	void onAABBCheck(BaseObject* other);

	Rhino_bullet(int xRhino,int yRhino,Direction directionRhino);
	Rhino_bullet();
	~Rhino_bullet();
};

