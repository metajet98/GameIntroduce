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
	{
		COLLISION->preventMove(this, other);
	}
}
void Camera::update()
{
	if (Stage::updating)
	{
		if (Stage::curStage->x - CAMERA->x > 0)
			dx = (Stage::curStage->x - CAMERA->x)*GAME_TIME->frameTime*1.5f +5;
		else
		{
			dx = 0;
			//ROCKMAN->dx = 0;
		}
		if (Stage::curStage->y - CAMERA->y > 0)
			dy = (Stage::curStage->y - CAMERA->y)*GAME_TIME->frameTime * 10;
		else
		{
			dy = 2;
			//ROCKMAN->dx = 0;
		}
		Stage::curStage->updating = false;
		ROCKMAN->pauseAnimation = false;
		return;
	}

	if ((ROCKMAN->x + ROCKMAN->dx < xCenter() && ROCKMAN->dx < 0  ) || (ROCKMAN->x + ROCKMAN->dx > xCenter() && ROCKMAN->dx > 0))
		dx = ROCKMAN->dx;
	else
		dx = 0;
	if ((ROCKMAN->y + ROCKMAN->dy < yCenter() && ROCKMAN->dy < 0) || (ROCKMAN->y + ROCKMAN->dy > yCenter() && ROCKMAN->dy > 0))
		dy = ROCKMAN->dy;
	else
		dy = 0;

	if (x + dx < Stage::curStage->left() && dx<0)
	{
		//x = Stage::curStage->left();
		dx = 0;
	}

	if (right() + dx > Stage::curStage->right() && dx>0)
	{
		//x = Stage::curStage->right() - width;
		dx = 0;
	}
}

Camera::Camera()
{
}



Camera::~Camera()
{
}
