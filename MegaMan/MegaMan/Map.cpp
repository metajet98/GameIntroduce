#include "Map.h"


void Map::init(const char* tileSheetPath, const char* objectsPath, const char* quadtreePath)
{
	TileMap::init(tileSheetPath, objectsPath);
	quadtree.init(quadtreePath, objects);
}
void Map::update()
{
	CAMERA->update();
	quadtree.update();
	ROCKMAN->update();

	List<BaseObject*>& groundsObject = CAMERA->objectsInCamera.grounds;

	for (int i = 0; i < groundsObject.size(); i++)
		COLLISION->checkCollision(ROCKMAN, groundsObject[i]);

	CAMERA->updateLocation();
	ROCKMAN->updateLocation();
	updateLocation();
}
void Map::draw()
{
	RECT r;
	SetRect(&r, xMap, yMap, xMap+VIEWPORT_WIDTH, yMap+VIEWPORT_HEIGHT);
	tileSheetImg.RenderTexture(0, 0, &r);
}
Map::Map()
{
	xMap = X_MAP;
	yMap = Y_MAP;
	viewportWidth = VIEWPORT_WIDTH;
	viewportHeight = VIEWPORT_HEIGHT;
	CAMERA->x = xMap;
	CAMERA->y = yMap;
	CAMERA->width = viewportWidth;
	CAMERA->height = viewportHeight;
}


Map::~Map()
{
}
