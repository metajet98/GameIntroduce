#pragma once
#include "List.h"
#include"BaseObject.h"
#include"RockButlet.h"
class ObjectsCategory
{
public:
	List<BaseObject*> grounds;
	List<BaseObject*> allObjects;
	List<BaseObject*> preventMoveCameras;


	void add(BaseObject* object);
	void remove(BaseObject* object);

	ObjectsCategory();
	~ObjectsCategory();
};

