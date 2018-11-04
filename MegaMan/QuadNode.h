#pragma once
#include "BaseObject.h"

class QuadNode : public RectF
{
public:
	int nObjects;
	int nNodes;
	BaseObject** objects;
	QuadNode* nodes;

	void init(fstream& fs, BaseObject** allObjects);

	QuadNode(void);
	~QuadNode(void);
};