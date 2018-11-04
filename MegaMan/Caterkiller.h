#pragma once
#include"Enermy.h"
#include"Camera.h"
#include<ctime>
#include"Caterkiller_bullet.h"

enum CATERKILLER_ACTIVITY
{
	CATERKILLER_STAND,
	CATERKILLER_MOVE,
	CATERKILLER_SHOT,
};

class Caterkiller: public Enermy
{
	static Caterkiller* instance;
public:
	static Caterkiller* getInstance();
	int UpDown;
	bool isMove;

	void draw();
	void update();
	void onCollision(BaseObject* S, int nx, int ny);
	void restore(BaseObject *obj);
	Caterkiller();
	~Caterkiller();
};

