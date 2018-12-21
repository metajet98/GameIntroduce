#pragma once
#include "Enermy.h"
#include "BlashHornet_Wing.h"
#include "DieEffect.h"
#include "Hornet.h"
#include "BlashHornet_Point.h"

enum BLASHHORNET_ACTION
{
	BLASHHORNET_DANCE,
	BLASHHORNET_ATT,
	BLASHHORNET_SHOT,
	BLASHHORNET_DIE,
	BLASHHORNET_FLY
};

class BlashHornet:public Enermy
{
	static BlashHornet* instance;
public:
	static BlashHornet* getInstance();

	static bool isDeath;
	static int lifeBoss;

	bool allowDraw;
	bool onHit;
	bool canUpdate;
	bool isATT;
	int posRockX, posRockY;
	POINT* ptsFly;
	GameTimeLoop damagedTime;
	GameTimeLoop timedie;
	GameTimeLoop timeAppear;
	GameTimeLoop timePerAnimation;
	GameTimeLoop timeShot;
	const float PI = 3.14f;
	float r,phi;
	int typeATT;
	RectF* re;
	
	void Move8_L_R();
	void Move8_R_L();
	void spawnChild();
	void spawnChildAndFollow();
	void update();
	void draw();
	void onCollision(BaseObject* other, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	void restore(BaseObject * obj);
	void updateDirecion();
	void updateChangeAnimation();
	void updateMove();
	void updateWing();
	void changeAction(int newAction);
	void updateLocation();
	BlashHornet();
	~BlashHornet();
};

