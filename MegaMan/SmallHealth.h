#pragma once
#include"Item.h"
class SmallHealth: public Item
{
public:
	void onAABBCheck(BaseObject* other);
	SmallHealth();
	~SmallHealth();
};

