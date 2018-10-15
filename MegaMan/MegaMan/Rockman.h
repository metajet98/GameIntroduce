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
	int isFalling;
	int isPushing;
	bool keyJumpPre;
	int updateX;

	int lifeNum;
	float shootSpeed;
	int maxBullet;
	//float _protectTime;
	GameTimeLoop timeDeath;


	bool onHit;
	bool isDeath;

	bool isShooting;

	FixedPoint8 m_xSpeed;
	FixedPoint8 m_ySpeed;

	FixedPoint8 m_xSpeedJumping;
	FixedPoint8 m_ySpeedJumping;

	FixedPoint8 m_ySpeedJumpReleased;
	FixedPoint8 m_ySpeedJumpReleasedMax;

	FixedPoint8 m_xSpeedRunning;

	FixedPoint8 m_ySpeedCollision;

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

