#pragma once
#include"List.h"
#include"Rockman.h"
#include"NotorBanger.h"
class NotoBanger_bullet:public MovableObject
{
	static List<NotoBanger_bullet*>* notobanger_bullet;
public:
	static List<NotoBanger_bullet*>* getListnotobanger_bullet();
	GameTimeLoop timeShot;

	void update();
	void draw();
	void onCollision(BaseObject* S, int nx, int ny);
	void onAABBCheck(BaseObject* other);

	NotoBanger_bullet(int xNotobanger, int yNotobanger, Direction directionNotobanger);
	NotoBanger_bullet();
	~NotoBanger_bullet();
};

