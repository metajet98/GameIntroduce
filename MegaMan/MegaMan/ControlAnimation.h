#pragma once
#include "Sprite.h"
#include"DrawableObject.h"
class ControlAnimation:public DrawableObject
{
	int countFrame;
	static ControlAnimation* instance;
public:
	static ControlAnimation* getInstance();
	int getCountFrame(int);
	void draw(Sprite *s,int &x,int &y,int &curAnimation,int &curFrame);
	ControlAnimation();
	~ControlAnimation();
};

