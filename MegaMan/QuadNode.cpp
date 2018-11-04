#include "QuadNode.h"

void QuadNode::init(fstream& fs, BaseObject** allObjects)
{
	fs >> x >> y >> width >> nNodes >> nObjects;
	height = width;

	if (nNodes > 0)
	{
		nodes = new QuadNode[4];
		nodes[0].init(fs, allObjects);
		nodes[1].init(fs, allObjects);
		nodes[2].init(fs, allObjects);
		nodes[3].init(fs, allObjects);

		return;
	}

	if (nObjects > 0)
	{
		int index;
		objects = new BaseObject*[nObjects];

		for (int i = 0; i < nObjects; i++)
		{
			fs >> index;
			objects[i] = allObjects[index];
		}

		return;
	}

	objects = 0;
	nodes = 0;
}

QuadNode::QuadNode(void)
{
}

QuadNode::~QuadNode(void)
{
}
