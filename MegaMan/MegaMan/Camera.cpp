#include "Camera.h"


Camera* Camera::instance = 0;
Camera * Camera::getInstance()
{
	if (instance == 0) instance = new Camera();
	return instance;
}

void Camera::update()
{
	if ((ROCKMAN->x + ROCKMAN->dx < xCenter() && ROCKMAN->dx < 0) || (ROCKMAN->x + ROCKMAN->dx > xCenter() && ROCKMAN->dx > 0))
		dx = ROCKMAN->dx;
	else
		dx = 0;
	if (x + dx < left() && dx < 0)
	{
		x = left();
		dx = 0;
	}

	if (right() + dx > right() && dx > 0)
	{
		x = right() - width;
		dx = 0;
	}
}

Camera::Camera()
{
}


Camera::~Camera()
{
}
