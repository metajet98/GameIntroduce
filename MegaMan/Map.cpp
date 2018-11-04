#include "Map.h"
#include"Dragonfly.h"
#include"NotorBanger.h"
#include"DieEffect.h"
#include"Caterkiller.h"
#include"HP_bar.h"

void Map::init(const char* tileSheetPath, const char* objectsPath, const char* quadtreePath)
{
	TileMap::init(tileSheetPath, objectsPath);
	quadtree.init(quadtreePath, objects);
}
void Map::initStage(const char * stageInfoPath)
{
	fstream fs(stageInfoPath);
	int nStage;
	fs >> nStage;

	for (int i = 0; i < nStage; i++)
		stages._Add(new Stage(fs, i));

	Stage::curStages = &stages;

	if (Stage::curStage == NULL)
		Stage::curStage = stages[0];
}
void Map::update()
{
	CAMERA->update();
	quadtree.update();
	ROCKMAN->update();
	//Stage::curStage->update();

	List<BaseObject*>& groundsObject = CAMERA->objectsInCamera.grounds;
	List<BaseObject*>& preventMoveCamerasObject = CAMERA->objectsInCamera.preventMoveCameras;
	List<Enermy*>& enermyObject = CAMERA->objectsInCamera.enermies;
	List<BaseObject*>& itemsObject = CAMERA->objectsInCamera.items;


	#pragma region Update

	HP_BAR->update();

	for (int i = 0; i < itemsObject.size(); i++)
	{
		itemsObject[i]->update();
	}

	for (int i = 0; i < enermyObject.size(); i++)
	{
		enermyObject[i]->update();
	}

	//update dan creep
	for (int i = 0; i < DRAGONFLY_BULLET->size(); i++)
	{
		DRAGONFLY_BULLET->at(i)->update();
	}

	for (int i = 0; i < NOTOBANGER_BULLET->size(); i++)
	{
		NOTOBANGER_BULLET->at(i)->update();
		NOTOBANGER_BULLET->at(i)->updateLocation();
	}

	for (List<RockButlet*>::Node* p = ROCKBUTLET->pHead; p; p = p->pNext)
	{
		RockButlet* bullet = p->m_value;
		bullet->update();
		for (int i = 0; i < enermyObject.size(); i++)
		{
			COLLISION->checkCollision(bullet, enermyObject[i]);
		}
		bullet->updateLocation();
	}
	for (List<DieEffect*>::Node *p = DieEffect::getList()->pHead; p; p = p->pNext)
	{
		DieEffect * effect = p->m_value;
		effect->update();
		effect->updateLocation();
	}
	for (int i = 0; i < CATERKILLER_BULLET->size(); i++)
	{
		CATERKILLER_BULLET->at(i)->update();
		CATERKILLER_BULLET->at(i)->updateLocation();
	}

#pragma endregion

	#pragma region CheckCollision
	for (int i = 0; i < groundsObject.size(); i++)
	{
		COLLISION->checkCollision(ROCKMAN, groundsObject[i]);

		for (int j = 0; j < enermyObject.size(); j++)
			COLLISION->checkCollision(enermyObject[j], groundsObject[i]);
		for (int j1 = 0; j1 < itemsObject.size(); j1++)
			COLLISION->checkCollision(itemsObject[j1], groundsObject[i]);
	}

	for (int i = 0; i < enermyObject.size(); i++)
	{
		COLLISION->checkCollision(ROCKMAN, enermyObject[i]);
		for (int j = 0; j < groundsObject.size(); j++)
			COLLISION->checkCollision(enermyObject[i], groundsObject[j]);
		enermyObject[i]->updateLocation();
	}

	for (int i = 0; i < itemsObject.size(); i++)
	{
		COLLISION->checkCollision(ROCKMAN, itemsObject[i]);
	}

	for (int i = 0; i < DRAGONFLY_BULLET->size(); i++)
	{
		COLLISION->checkCollision(ROCKMAN, DRAGONFLY_BULLET->at(i));
	}
	for (int i = 0; i < NOTOBANGER_BULLET->size(); i++)
	{
		COLLISION->checkCollision(ROCKMAN, NOTOBANGER_BULLET->at(i));
	}
	for (int i = 0; i < CATERKILLER_BULLET->size(); i++)
	{
		COLLISION->checkCollision(ROCKMAN, CATERKILLER_BULLET->at(i));
	}
#pragma endregion

	#pragma region Delete
	//xoa dan khoi camera
	for (int i = 0; i < ROCKBUTLET->Count; i++)
	{
		RockButlet* bullet = ROCKBUTLET->at(i);
		ROCKBUTLET->at(i)->updateLocation();
		if (!COLLISION->AABBCheck(*bullet, *CAMERA) || bullet->allowDelete)
		{
			ROCKBUTLET->_Remove(bullet);
			delete bullet;

		}
	}
	//xoa dan creep khoi camera
	for (int i = 0; i < DRAGONFLY_BULLET->size(); i++)
	{
		DRAGONFLY_BULLET->at(i)->updateLocation();
		if (!COLLISION->AABBCheck(*DRAGONFLY_BULLET->at(i), *CAMERA) || DRAGONFLY_BULLET->at(i)->allowDelete)
		{
			Dragonfly_bullet *db = DRAGONFLY_BULLET->at(i);
			DRAGONFLY_BULLET->_Remove(db);
			delete db;
		}
	}
	for (int i = 0; i < NOTOBANGER_BULLET->size(); i++)
	{
		NOTOBANGER_BULLET->at(i)->updateLocation();
		if (!COLLISION->AABBCheck(*NOTOBANGER_BULLET->at(i), *CAMERA) || NOTOBANGER_BULLET->at(i)->allowDelete)
		{
			NotoBanger_bullet *db = NOTOBANGER_BULLET->at(i);
			NOTOBANGER_BULLET->_Remove(db);
			delete db;
		}
	}
	for (int i = 0; i < DieEffect::getList()->size(); i++)
	{
		DieEffect* effect = DieEffect::getList()->at(i);
		if (!COLLISION->AABBCheck(*effect, *CAMERA))
		{
			DieEffect::getList()->_Remove(effect);
			delete effect;
		}
	}
	for (int i = 0; i < CATERKILLER_BULLET->size(); i++)
	{
		CATERKILLER_BULLET->at(i)->updateLocation();
		if (!COLLISION->AABBCheck(*CATERKILLER_BULLET->at(i), *CAMERA) || CATERKILLER_BULLET->at(i)->allowDelete)
		{
			Caterkiller_bullet *cb = CATERKILLER_BULLET->at(i);
			CATERKILLER_BULLET->_Remove(cb);
			delete cb;
		}
	}
#pragma endregion


	ROCKMAN->updateLocation();
	CAMERA->updateLocation();
	updateLocation();
}
void Map::draw()
{
	RECT r;
	SetRect(&r, xMap, yMap, xMap+VIEWPORT_WIDTH, yMap+VIEWPORT_HEIGHT);
	tileSheetImg.RenderTexture(0, 0, &r);

	HP_BAR->draw();

	List<Enermy*> enermyObject = CAMERA->objectsInCamera.enermies;
	List<BaseObject*>& itemsObject = CAMERA->objectsInCamera.items;

	for (int i = 0; i < itemsObject.size(); i++)
	{
		itemsObject[i]->draw();
	}

	for (int i = 0; i < enermyObject.size(); i++)
	{
		enermyObject[i]->draw();
		
	}
	for (int i = 0; i < DRAGONFLY_BULLET->size(); i++)
	{
		DRAGONFLY_BULLET->at(i)->draw();
	}
	for (int i = 0; i < NOTOBANGER_BULLET->size(); i++)
	{
		NOTOBANGER_BULLET->at(i)->draw();
	}
	for (int i = 0; i < DieEffect::getList()->size(); i++)
	{
		DieEffect::getList()->at(i)->draw();
	}
	for (int i = 0; i < CATERKILLER_BULLET->size(); i++)
	{
		CATERKILLER_BULLET->at(i)->draw();
	}
}
void Map::restoreAllObject()
{
	for (int i = 0; i < nObjects; i++)
		if (objects[i]->id >= 0)
		{
			DrawableObject* drawableObject = (DrawableObject*)objects[i];
			drawableObject->restore(objects[i]);
		}
}
void Map::updateLocation()
{
	xMap += CAMERA->dx;
	yMap += CAMERA->dy;
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
