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
	List<BaseObject*>& preventMoveCamerasObject = CAMERA->objectsInCamera.preventMoveCameras;
	List<Enermy*> enermyObject = CAMERA->objectsInCamera.enermies;

	for (int i = 0; i < enermyObject.size(); i++)
	{
		enermyObject[i]->update();
		COLLISION->checkCollision(ROCKMAN, enermyObject[i]);
		enermyObject[i]->updateLocation();
	}

	for (List<RockButlet*>::Node* p = ROCKBUTLET->pHead; p; p = p->pNext)
	{
		RockButlet* bullet = p->m_value;
		bullet->update();
		//bullet->updateLocation();

	}

	for (int i = 0; i < ROCKBUTLET->Count; i++)
	{
		RockButlet* bullet = ROCKBUTLET->at(i);
		if (!COLLISION->AABBCheck(*bullet, *CAMERA))
		{
			ROCKBUTLET->_Remove(bullet);
			delete bullet;
			i--;
		}
	}

	for (int i = 0; i < groundsObject.size(); i++)
	{
		COLLISION->checkCollision(ROCKMAN, groundsObject[i]);

		for (int j = 0; j < enermyObject.size(); j++)
			COLLISION->checkCollision(enermyObject[j], groundsObject[i]);
	}

	for (int i = 0; i < enermyObject.size(); i++)
	{
		COLLISION->checkCollision(ROCKMAN, enermyObject[i]);
	}

	ROCKMAN->updateLocation();
	CAMERA->updateLocation();
	updateLocation();
}
void Map::draw()
{
	RECT r;
	SetRect(&r, xMap, yMap, xMap+VIEWPORT_WIDTH, yMap+VIEWPORT_HEIGHT);
	tileSheetImg.RenderTexture(0, 0, &r);

	List<Enermy*> enermyObject = CAMERA->objectsInCamera.enermies;

	for (int i = 0; i < enermyObject.size(); i++)
	{
		enermyObject[i]->draw();
		
	}
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
