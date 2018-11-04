#pragma once
#include "QuadNode.h"

class QuadTree
{
public:
	QuadNode rootNode;

	void init(const char* quadtreePath, BaseObject** allObjects);
	void fillObjectToCameraFromNode(QuadNode* node);
	void removeObjectFromCamera();
	void update();

	QuadTree(void);
	~QuadTree(void);
};

