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

class Rockman:public MovableObject
{
	int inAir;
	int isPushing;
	int isSliding;
	bool invisible;
	bool allowDraw;
	bool pauseAnimation;
	bool lastStatusRunAttack;

	static Rockman* instance;
public:
	static Rockman* getInstance();
	bool onHit;

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

