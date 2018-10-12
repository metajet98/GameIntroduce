#include "OldRestore.h"
#include"BaseObject.h"


void OldRestore::getFromObject(BaseObject * obj)
{
	oldX = obj->x;
	oldY = obj->y;
}

void OldRestore::restore(BaseObject * obj)
{
	obj->x = oldX;
	obj->y = oldY;
}

OldRestore::OldRestore()
{
}


OldRestore::~OldRestore()
{
}
