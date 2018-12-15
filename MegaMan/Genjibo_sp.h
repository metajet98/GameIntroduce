#pragma once
#include "Enermy.h"
//#include "Genjibo.h"
class Genjibo_sp: public Enermy
{
	static Genjibo_sp* instance;
public:
	static Genjibo_sp* getInstance();
	bool isActive;
	GameTimeLoop timeStand;

	void draw();
	void update();
	void restore(BaseObject* obj);
	void updateMove();
	Genjibo_sp();
	~Genjibo_sp();
};

