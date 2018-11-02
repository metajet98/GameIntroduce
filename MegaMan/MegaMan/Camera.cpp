#include "Camera.h"
#include"Stage.h"

Camera* Camera::instance = 0;
Camera * Camera::getInstance()
{
	if (instance == 0) instance = new Camera();
	return instance;
}


void Camera::onCollision(BaseObject* other, int nx, int ny)
{
	if (other->collisionType == CT_PREVENTMOVECAMERA)
		COLLISION->preventMove(this, other);
}
void Camera::update()
{
	if ((ROCKMAN->y + ROCKMAN->dy < yCenter() && ROCKMAN->dy < 0) || (ROCKMAN->y + ROCKMAN->dy > yCenter() && ROCKMAN->dy > 0))
		dy = ROCKMAN->dy;
	else
		dy = 0;
	if ((ROCKMAN->x + ROCKMAN->dx < xCenter() && ROCKMAN->dx < 0) || (ROCKMAN->x + ROCKMAN->dx > xCenter() && ROCKMAN->dx > 0))
		dx = ROCKMAN->dx;
	else
		dx = 0;
	if (x + dx < 5&& dx < 0)
	{
		x = 5;
		dx = 0;
	}

	/*if (x + dx < Stage::curStage->left() && x>=Stage::curStage->left())
	{
		dx = Stage::curStage->left()-x;
	}

	if (right() + dx > Stage::curStage->right() && right()<=Stage::curStage->right())
	{
		dx = Stage::curStage->right() - width;
	}*/
}

Camera::Camera()
{
}



Camera::~Camera()
{
}
