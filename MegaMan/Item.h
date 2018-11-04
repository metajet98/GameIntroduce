#pragma once
#include"MovableObject.h"
#include"List.h"
#include"Rockman.h"

class Item:public MovableObject
{
	static List<Item*>* items;
public:
	static List<Item*>* getListItem();

	virtual void onAABBCheck(BaseObject* other);
	virtual void onCollision(BaseObject* other, int nx, int ny);
	virtual void restore(BaseObject* obj);
	virtual void update();
	Item();
	~Item();
};

