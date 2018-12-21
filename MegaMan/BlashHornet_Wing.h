#pragma once
#include"MovableObject.h"
#include "BlashHornet.h"
class BlashHornet_Wing:public MovableObject
{
	static BlashHornet_Wing* instance;
public:
	static BlashHornet_Wing* getInstance();

	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	//void updateLocation();

	BlashHornet_Wing();
	~BlashHornet_Wing();
};

