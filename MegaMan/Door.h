#pragma once
#include"DrawableObject.h"
#include"Rockman.h"

class Door:public DrawableObject
{
public:
	bool isOpen;
	bool isClose;

	void draw();
	void update();
	void Open();
	void Close();
	void onCollision(BaseObject*S, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	Door();
	Door(int x, int y, int w, int h);
	~Door();
};

