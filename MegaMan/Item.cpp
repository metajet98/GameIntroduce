#include "Item.h"


List<Item*>* Item::items = 0;
List<Item*>* Item::getListItem()
{
	if(items==0)
		items = new List<Item*>();
	return items;
}

void Item::onAABBCheck(BaseObject * other)
{
	if (other == ROCKMAN)
	{
		this->alive = false;
	}
}

void Item::onCollision(BaseObject * other, int nx, int ny)
{
	MovableObject::onCollision(other, nx, ny);
}

void Item::restore(BaseObject * obj)
{
	dy = 0;
	vy = 0;
	DrawableObject::restore(obj);
}

void Item::update()
{
	DrawableObject::update();
}

Item::Item()
{
	vy = 0;
	ay = 0;
	vx = 0;
	collisionType = CT_ITEM;
	gameTimeLoop.init(3, 1);
}


Item::~Item()
{
}
