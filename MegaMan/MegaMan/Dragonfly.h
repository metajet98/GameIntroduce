#pragma once
#include"Enermy.h"
#include"Dragonfly_bullet.h"
#include"Camera.h"
enum DRAGONFLY_ACTIVITY
{
	DRAGONFLY_FLY,
	DRAGONFLY_SHOT,
	DRAGONFLY_END_SHOT,
};
class Dragonfly: public Enermy
{
private:
	DRAGONFLY_ACTIVITY dragonflyActivity;
	static Dragonfly* instance;
public:
	static Dragonfly* getInstance();


	void draw();
	void update();
	void onCollision(BaseObject* S, int nx, int ny);
	void restore(BaseObject *obj);
	Dragonfly();
	~Dragonfly();
};

