#pragma once
#include"DrawableObject.h"
#include"Map.h"

class LifeUI:public DrawableObject
{
	static LifeUI* instance;
public:
	static LifeUI* getInstance();

	virtual void next(int& curFrame);
	virtual void draw();
	void updateLocation();
	LifeUI();
	~LifeUI();
};

