#pragma once
#include "Texture.h"
#include "BaseObject.h"
#include <fstream>
#include"DrawableObject.h"
using namespace std;

class TileMap
{
public:
	float viewportWidth, viewportHeight;
	float xMap, yMap;
	int nObjects;
	BaseObject** objects;
	static TileMap* curMap;
	Texture tileSheetImg;

	void convertToViewportPos(int xInMap, int yInMap, int& xViewport, int& yViewport);
	void updateLocation();
	void init(const char* tileSheetPath, const char* objectsPath);
	void initObjects(const char* objectsPath);

	TileMap();
	~TileMap();
};

