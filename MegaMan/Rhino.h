#pragma once
#include"Enermy.h"
#include<time.h>
#include"Rhino_bullet.h"
#include"HP_bar.h"
#include"HP_Boss.h"
enum RHINO_ACTION
{
	RA_STAND,
	RA_MOVE,
	RA_ATT,
	RA_SHOT,
	RA_IsDAMAGED,
	RA_MOVE_ATT
};
class Rhino:public Enermy
{
	static Rhino* instance;
public:
	static Rhino* getInstance();
	bool appearHP;
	bool invisible;
	bool allowDraw;
	bool onHit;
	float animation_dalaytime;
	bool isDeath;
	GameTimeLoop damagedTime;
	GameTimeLoop timePerAnimation;

	void draw();
	void update();
	void updateMove();
	void onCollision(BaseObject* other, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	void setOnHit(bool newOnHit);;
	void die();
	void restore(BaseObject* obj);
	void changeAction(int newAction);
	RHINO_ACTION randomAnimation();
	Rhino();
	~Rhino();
};

