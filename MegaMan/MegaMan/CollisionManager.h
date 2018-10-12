#pragma once
#include"BaseObject.h"


class CollisionManager
{
private:
	static CollisionManager*instance;
public:
	static CollisionManager*getInstance();

	RectF getBroadphaseBox(Box& M);
	bool AABBCheck(RectF& M, RectF& S);
	float sweptAABB(Box* M, RectF* S, int& normalX, int& normalY);
	void checkCollision(BaseObject*M, BaseObject*S);
	void preventMove(BaseObject*M, BaseObject*S);

	CollisionManager();
	~CollisionManager();
};

