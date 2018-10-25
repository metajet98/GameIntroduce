#include "Dragonfly.h"

Dragonfly* Dragonfly::instance = 0;

Dragonfly * Dragonfly::getInstance()
{
	if (instance == 0)
		instance = new Dragonfly();
	return instance;
}

void Dragonfly::draw()
{
	Enermy::draw();
}

void Dragonfly::update()
 {
	//Enermy::update();
	vx = direction * 40;
	dx = vx * TIME;
	DrawableObject::update();
}

void Dragonfly::onCollision(BaseObject * S, int nx, int ny)
{
	Enermy::onCollision(S, nx, ny);
	if (S->collisionType == CT_GROUND && nx != 0)
		direction = (Direction)nx;
}

Dragonfly::Dragonfly()
{
	sprite = SPRITEMANAGER->sprites[SPR_DRAGONFLY];
	direction = Right;
	curAnimation = DRAGONFLY_FLY;
	curFrame = 0;
	/*x = 445;
	y = 371;*/

	x = 74;
	y = 545;
}


Dragonfly::~Dragonfly()
{
}
