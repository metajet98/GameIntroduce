#include "ObjectsCategory.h"


void ObjectsCategory::add(BaseObject* object)
{
	switch (object->collisionType)
	{
	case CT_GROUND:
		grounds._Add(object);
	}
	allObjects._Add(object);
}
void ObjectsCategory::remove(BaseObject * object)
{
	switch (object->collisionType)
	{
	case CT_GROUND:
		grounds._Remove(object);
	}
	allObjects._Remove(object);
}
ObjectsCategory::ObjectsCategory()
{

}


ObjectsCategory::~ObjectsCategory()
{
}
