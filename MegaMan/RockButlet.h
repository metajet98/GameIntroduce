#pragma once
#include"MovableObject.h"
#include"List.h"
#include"Rockman.h"
#include<vector>
#include"Enermy.h"

class RockButlet:public MovableObject
{
private:
	bool inFlight;
	
	static List<RockButlet*>* bullets;
public:
	static List<RockButlet*>* getListBullet();
	CATEGORY_BULLET_FOR_MEGAMAN categoryBullet;

	void draw();
	void update();
	void onCollision(BaseObject* S, int nx, int ny);
	void onAABBCheck(BaseObject * other);
	void changeDirection(Direction dir);
	RockButlet(CATEGORY_BULLET_FOR_MEGAMAN level);
	RockButlet(CATEGORY_BULLET_FOR_MEGAMAN level,Direction dir);
	~RockButlet();
};

