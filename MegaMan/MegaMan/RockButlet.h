#pragma once
#include"MovableObject.h"
#include"List.h"
#include"Rockman.h"
#include<vector>
class RockButlet:public MovableObject
{
private:
	bool inFlight;

	static List<RockButlet*>* bullets;
public:
	static List<RockButlet*>* getListBullet();

	float t;
	float x0, y0, x1, y1, x2, y2, x3, y3, x4, y4;
	void draw();
	void update();
	void onCollision(BaseObject* S, int nx, int ny);
	RockButlet();
	~RockButlet();
};

