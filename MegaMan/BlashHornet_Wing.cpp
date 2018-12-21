#include "BlashHornet_Wing.h"


BlashHornet_Wing * BlashHornet_Wing::instance = 0;
BlashHornet_Wing * BlashHornet_Wing::getInstance()
{
	if (instance == 0)
		instance = new BlashHornet_Wing();
	return instance;
}

void BlashHornet_Wing::update()
{
	updateLocation();
	MovableObject::update();
}

void BlashHornet_Wing::draw()
{
	if (sprite == 0) return;

	
	int xInViewport, yInViewport;
	TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);


	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
}

void BlashHornet_Wing::onCollision(BaseObject * other, int nx, int ny)
{
	MovableObject::onCollision(other, nx, ny);

}

//void BlashHornet_Wing::updateLocation()
//{
//	x += BLASHHORNET->dx;
//	y += BLASHHORNET->dy;
//}


BlashHornet_Wing::BlashHornet_Wing()
{
	sprite = SPRITEMANAGER->sprites[SPR_BLASHHORNET_WING];
	curAnimation = 0;
	curFrame = 0;
	x = BLASHHORNET->x-20;
	y = BLASHHORNET->y-23;
	ay = 0;
}


BlashHornet_Wing::~BlashHornet_Wing()
{
	
}
