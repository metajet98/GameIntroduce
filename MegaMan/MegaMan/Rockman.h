#pragma once
#include "MovableObject.h"
#include"Constant.h"
#include"KeyBoard.h"
#include"KeyGame.h"
#include"TileMap.h"
#include"FixedPoint8.h"
#include"ControlAnimation.h"

class Rockman:public MovableObject
{
	int inAir;
	int isPushing;

	bool pauseAnimation;
	bool lastStatusRunAttack;

	static Rockman* instance;
public:
	static Rockman* getInstance();

	void onCollision(BaseObject*S,int nx,int ny);
	void onCollisionPush(BaseObject*S, int nx, int ny);
	void updateLocation();
	void update();
	void updateDirection();
	void updateChangeAnimation();
	void draw();
	void changeAction(int newAction);

	Rockman();

	~Rockman();
};

