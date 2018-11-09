#pragma once
#include"Enermy.h"
#include<time.h>
enum RHINO_ACTION
{
	RA_STAND,
	RA_MOVE,
	RA_ATT,
	RA_SHOT,
	RA_IsDAMAGED,
};
class Rhino:public Enermy
{
	static Rhino* instance;
public:
	static Rhino* getInstance();

	bool appearHP;
	bool isBlink;
	bool allowDraw;
	bool onHit;
	GameTimeLoop BlinkTime;
	GameTimeLoop damagedTime;
	GameTimeLoop timePerAnimation;

	void updateBlink();
	void draw();
	void update();
	void onCollision(BaseObject* other, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	void setOnHit(bool newOnHit);
	void updateMach();
	void die();
	void restore(BaseObject* obj);
	void changeAction(int newAction);
	RHINO_ACTION randomAnimation();
	Rhino();
	~Rhino();
};

