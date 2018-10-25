#pragma once
#include "List.h"
#include"BaseObject.h"
#include"RockButlet.h"
#include"Enermy.h"
class ObjectsCategory
{
public:
	List<BaseObject*> grounds;
	List<BaseObject*> allObjects;
	List<BaseObject*> preventMoveCameras;
	List<Enermy*> enermies;


	void add(BaseObject* object);
	void remove(BaseObject* object);

	ObjectsCategory();
	~ObjectsCategory();
};

