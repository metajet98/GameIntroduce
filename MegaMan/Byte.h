#pragma once
#include "Enermy.h"
#include "Byte_bullet.h"
#include "DoorCanMove.h"
enum BYTE_ACTION
{
	BYTE_STAND,
	BYTE_MOVE,
	BYTE_SHOT,
	BYTE_ATT
};
enum FRAME_TYPE
{
	HEIGHT_80,
	HEIGHT_74,
	HEIGHT_84,
	HEIGHT_91
};
class Byte: public Enermy
{
	static Byte* instance;
public:
	static Byte* getInstance();
	FRAME_TYPE frameType;
	bool allowDraw;
	GameTimeLoop damagedTime;
	GameTimeLoop timePerAnimation;
	GameTimeLoop timeShoot;
	GameTimeLoop timeMove;

	void draw();
	void update();
	void updateMove();
	void onLastFrameAnimation(BYTE_ACTION ba);
	void updateHeight();
	void onCollision(BaseObject* other, int nx, int ny);
	void onAABBCheck(BaseObject* other);
	void restore(BaseObject* obj);
	void changeAction(int newAction);
	Byte();
	~Byte();
};

