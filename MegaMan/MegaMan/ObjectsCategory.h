#pragma once
#include "List.h"
#include"BaseObject.h"
class ObjectsCategory
{
public:
	List<BaseObject*> grounds;
	List<BaseObject*> allObjects;

	void add(BaseObject* object);
	void remove(BaseObject* object);

	ObjectsCategory();
	~ObjectsCategory();
};

