#include "ObjectsCategory.h"


void ObjectsCategory::add(BaseObject* object)
{
	switch (object->collisionType)
	{
	case CT_GROUND:
		grounds._Add(object);
		break;
	case CT_PREVENTMOVECAMERA:
		preventMoveCameras._Add(object);
		break;
	case CT_ENERMY:
		enermies._Add((Enermy*)object);
		break;
	}
	allObjects._Add(object);
}
void ObjectsCategory::remove(BaseObject * object)
{
	switch (object->collisionType)
	{
	case CT_GROUND:
		grounds._Remove(object);
		break;
	case CT_PREVENTMOVECAMERA:
		preventMoveCameras._Remove(object);
		break;
	case CT_ENERMY:
		enermies._Remove((Enermy*)object);
		break;
	}
	allObjects._Remove(object);
}
ObjectsCategory::ObjectsCategory()
{

}


ObjectsCategory::~ObjectsCategory()
{
}
