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
	CATEGORY_BULLET_FOR_MEGAMAN categoryBullet;
	static List<RockButlet*>* bullets;
public:
	static List<RockButlet*>* getListBullet();
	

	void draw();
	void update();
	void onCollision(BaseObject* S, int nx, int ny);
	RockButlet();
	~RockButlet();
};

