#pragma once
#include"Enermy.h"
#include"Camera.h"
#include"NotoBanger_bullet.h"

enum NOTORBANGER_ACTIVITY
{
	NOTORBANGER_STAND,
	NOTORBANGER_JUMP,
	NOTORBANGER_SHOT,
};

class NotorBanger:public Enermy
{
	NOTORBANGER_ACTIVITY activity;
	static NotorBanger* instance;
	//bool changeDirection;
public:
	static NotorBanger* getInstance();
	GameTimeLoop timeStand;
	GameTimeLoop timeShot;
	int countJump;

	void draw();
	void update();
	void onCollision(BaseObject* S, int nx, int ny);
	void restore(BaseObject *obj);

	NotorBanger();
	~NotorBanger();
};

