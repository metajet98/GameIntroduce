#pragma once
#include"DrawableObject.h"
#include"Map.h"
#include"Constant.h"

class HP_bar:public DrawableObject
{
	static HP_bar* instance;
	Sprite* sprite_BOSS;
	int curFrame_Boss;
	int curAnimation_Boss;
public:
	static HP_bar* getInstance();

    void draw();
	void update();
	void updateLocation();
	HP_bar();
	~HP_bar();
};

