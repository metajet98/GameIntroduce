#pragma once
#include "MovableObject.h"
#include"Constant.h"
#include"KeyBoard.h"
#include"KeyGame.h"
#include"TileMap.h"

enum BULLET_TYPE
{
	ST_FIRE,
	ST_FROZEN,
};
class Rockman:public MovableObject
{
	int updateX;

	int lifeNum;
	float shootSpeed;
	int maxBullet;
	//float _protectTime;
	GameTimeLoop timeDeath;


	bool onHit;
	bool isDeath;

	static Rockman* instance;
public:
	static Rockman* getInstance();

	void onCollision(BaseObject*S,int nx,int ny);
	void updateLocation();
	void update();
	void draw();
	void changeAction(int newAction);

	Rockman();

	~Rockman();
};

