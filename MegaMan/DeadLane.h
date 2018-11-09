#pragma once
#include"DrawableObject.h"
#include"Rockman.h"
class DeadLane: public DrawableObject
{
	static DeadLane* instance;
public:
	static DeadLane* getInstance();
	void onAABBCheck(BaseObject * other);
	void onCollision(BaseObject* other, int nx, int ny);
	DeadLane();
	~DeadLane();
};

