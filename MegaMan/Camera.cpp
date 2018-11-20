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
		if (Stage::curStage->xPre - CAMERA->x > 0)
			dx = (Stage::curStage->xPre - CAMERA->x)*GAME_TIME->frameTime*1.5f +5;
		else
		{
			dx = 2;
		}
		if (Stage::curStage->yPre - CAMERA->y > 0)
			dy = (Stage::curStage->yPre - CAMERA->y)*GAME_TIME->frameTime * 10;
		else
		{
			dy = 2;
		}
		/*if (x > Stage::curStage->x || y> Stage::curStage->y)
		{
			Stage::curStage->updating = false;
			ROCKMAN->pauseAnimation = false;
		}*/
		return;
	}

	if ((ROCKMAN->x + ROCKMAN->dx < xCenter() && ROCKMAN->dx < 0 && !Stage::updating ) || (ROCKMAN->x + ROCKMAN->dx > xCenter() && ROCKMAN->dx > 0 && !Stage::updating))
		dx = ROCKMAN->dx;
	else
		dx = 0;
	if ((ROCKMAN->y + ROCKMAN->dy < yCenter() && ROCKMAN->dy < 0 && !Stage::updating) || (ROCKMAN->y + ROCKMAN->dy > yCenter() && ROCKMAN->dy > 0 && !Stage::updating))
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
