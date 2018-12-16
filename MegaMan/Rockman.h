#pragma once
#include "MovableObject.h"
#include"Constant.h"
#include"KeyBoard.h"
#include"KeyGame.h"
#include"TileMap.h"
#include"FixedPoint8.h"
#include<DirectXMath.h>
#include"RockButlet.h"
#include"DieEffect.h"
#include"Effect_Power.h"
#include"Stage.h"
#include"Scene.h"


class Rockman:public MovableObject
{
	int isCharging;
	Direction pushDirection;
	int isSliding;
	GameTimeLoop timePushJump;
	
	bool lastStatusRunAttack;

	static Rockman* instance;
public:
	static Rockman* getInstance();
	bool allowDraw;
	bool onHit;
	bool invisible;
	bool isDeath;
	bool pauseAnimation;
	bool onAreaBoss;
	bool onAreaBossSub;
	int doorCollision;
	int NumberOfLife;
	int isPushing;

	GameTimeLoop timeCharging;
	GameTimeLoop timeCharging1;
	GameTimeLoop timeDeath;

	void onCollision(BaseObject*S,int nx,int ny);
	void onCollisionPush(BaseObject*S, int nx, int ny);
	void updateLocation();
	void update();
	void updateDirection();
	void updateChangeAnimation();
	void draw();
	void changeAction(int newAction);
	void setOnHit(bool newOnHit);
	void updateInvisible();
	void die();

	Rockman();

	~Rockman();
};

