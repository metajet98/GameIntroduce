#pragma once
#include"TileMap.h"
#include "Camera.h"
#include"QuadTree.h"
#include"Stage.h"

class Map:public TileMap
{
public:
	QuadTree quadtree;
	List<Stage*> stages;
	Door** doors;

	void init(const char* tileSheetPath, const char* objectsPath, const char* quadtreePath);
	void initStage(const char* stageInfoPath);

	void update();
	void draw();
	void restoreAllObject();
	void updateLocation();
	Map();
	~Map();
};

