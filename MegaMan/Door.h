#pragma once
#include"MovableObject.h"
#include"Rockman.h"

class Door:public MovableObject
{
public:
	bool isOpen;
	bool isClose;
	bool updating;

	void draw();
	void update();
	void updateFrame();
	void Open();
	void Close();
	void onCollision(BaseObject*S, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	Door();
	Door(int x, int y, int w, int h);
	~Door();
};

