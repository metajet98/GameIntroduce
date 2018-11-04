#pragma once
#include "CollisionManager.h"
#include "DrawableObject.h"

class MovableObject : public DrawableObject
{
public:
	bool isOnGround;

	void updateVerlocity();
	virtual void update();
	virtual void draw();
	virtual void onCollision(BaseObject* other, int nx, int ny);

	MovableObject();
	~MovableObject();
};