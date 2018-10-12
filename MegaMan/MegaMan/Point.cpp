#include "Point.h"

Point::Point(int x, int y)
{
	init(x, y);
}

void Point::init(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point::~Point()
{
}
