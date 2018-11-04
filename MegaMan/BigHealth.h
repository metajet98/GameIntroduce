#pragma once
#include"Item.h"
class BigHealth: public Item
{
public:
	void onAABBCheck(BaseObject* other);
	BigHealth();
	~BigHealth();
};

