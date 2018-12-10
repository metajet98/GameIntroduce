#pragma once
#include "MovableObject.h"
#include "List.h"
#include "TileMap.h"
class Byte_bullet: public MovableObject
{
	static List<Byte_bullet*>* instance;
public:
	static List<Byte_bullet*>* getInstance();

	void update();
	void draw();
	void onCollision(BaseObject* S, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	Byte_bullet();
	Byte_bullet(int xByte,int yByte,Direction dir);
	~Byte_bullet();
};

