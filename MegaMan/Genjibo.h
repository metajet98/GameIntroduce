#pragma once
#include "Enermy.h"
#include "Map.h"
#include "DoorCanMove.h"
enum GENJIBO_ACTION
{
	GENJIBO_APPEAR,
	GENJIBO_MOVE,
	GENJIBO_DAMAGED,
	GENJIBO_ROLATE,
	GENJIBO_STAND
};
class Genjibo: public Enermy
{
	static Genjibo* instance;
public:
	static Genjibo* getInstance();

	bool onHit;
	bool canMoveOnWall;
	bool appear;
	Direction upDown;

	float animation_delaytime;
	GameTimeLoop damagedTime;
	GameTimeLoop timePerAnimation;
	GameTimeLoop timeJump;
	int countJump;

	void draw();
	void update();
	void updateMove();
	void mech();
	void onLastFrameAnimation(GENJIBO_ACTION ga);
	void onCollision(BaseObject* other, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	void setOnHit(bool newOnHit);;
	void restore(BaseObject* obj);
	void changeAction(int newAction);

	Genjibo();
	~Genjibo();
};

