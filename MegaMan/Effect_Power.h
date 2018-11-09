#pragma once
#include"MovableObject.h"
#include"TileMap.h"
#include"Rockman.h"
class Effect_Power: public MovableObject
{
	static Effect_Power* instance;
public:
	static Effect_Power* getInstance();
	void draw();
	void update();
	Effect_Power();
	~Effect_Power();
};

