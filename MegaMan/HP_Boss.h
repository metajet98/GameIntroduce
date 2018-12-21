#pragma once
#include"DrawableObject.h"
#include"Map.h"
#include"Constant.h"
#include"BlashHornet.h"
class HP_Boss:public DrawableObject
{
	static HP_Boss* instance;
public:
	static HP_Boss* getInstance();

	void draw();
	void update();
	void updateLocation();

	HP_Boss();
	~HP_Boss();
};

