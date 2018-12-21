#pragma once
#include "Enermy.h"
#include "List.h"

class Hornet:public Enermy
{
	static List<Hornet*>* instance;
public:
	static List<Hornet*>* getInstance();

	GameTimeLoop timeDie;
	int type;

	void draw();
	void update();
	void onCollision(BaseObject* other, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	Hornet(int xBoss, int yBoss, Direction dirBoss,int _vx,int _vy,int _type);
	Hornet();
	~Hornet();
};

