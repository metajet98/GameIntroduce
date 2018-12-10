#pragma once
#include "Enermy.h"
enum GENJIBO_ACTION
{
	GENJIBO_STAND,
	GENJIBO_MOVE,
	GENJIBO_DAMAGED
};
class Genjibo: public Enermy
{
	static Genjibo* instance;
public:
	static Genjibo* getInstance();

	bool onHit;
	bool canMoveOnWall;
	float animation_delaytime;
	GameTimeLoop damagedTime;
	GameTimeLoop timePerAnimation;
	GameTimeLoop timeJump;

	void draw();
	void update();
	void updateMove();
	void onCollision(BaseObject* other, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	void setOnHit(bool newOnHit);;
	void restore(BaseObject* obj);
	void changeAction(int newAction);

	Genjibo();
	~Genjibo();
};

