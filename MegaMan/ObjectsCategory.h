#pragma once
#include "List.h"
#include"BaseObject.h"
#include"RockButlet.h"
#include"Enermy.h"
#include"Item.h"
class ObjectsCategory
{
public:
	List<BaseObject*> grounds;
	List<BaseObject*> allObjects;
	List<BaseObject*> preventMoveCameras;
	List<BaseObject*> items;
	List<Enermy*> enermies;
	List<BaseObject*> traps;

	void add(BaseObject* object);
	void remove(BaseObject* object);

	ObjectsCategory();
	~ObjectsCategory();
};

