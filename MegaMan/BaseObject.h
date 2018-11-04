#pragma once
#include<iostream>

#include"Box.h"
#include"OldRestore.h"
#include "Constant.h"
#include"GameTime.h"
#include"Sprite.h"


extern void* operator new(std::size_t sz); //Lấy float cho phép toán


class BaseObject :public Box, public OldRestore
{
public:
	COLLISION_TYPE collisionType;
	int id;
	bool isCollisionCross;
	bool isCollision;
	bool alive;
	int life;
	bool allowDelete;

	virtual void update();
	virtual void draw();
	virtual void onCollision(BaseObject* other, int nx, int ny);
	virtual void onAABBCheck(BaseObject* other);
	virtual void updateLocation();
	RectF oldRect();

	BaseObject();
	~BaseObject();
};

