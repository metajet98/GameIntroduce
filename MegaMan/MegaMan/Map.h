#pragma once
#include"TileMap.h"
#include "Camera.h"
#include"QuadTree.h"
class Map:public TileMap
{
public:
	QuadTree quadtree;

	void init(const char* tileSheetPath, const char* objectsPath, const char* quadtreePath);
	void update();
	void draw();
	Map();
	~Map();
};

