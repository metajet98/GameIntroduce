#include "Map.h"
#include"Dragonfly.h"
#include"NotorBanger.h"
#include"DieEffect.h"
#include"Caterkiller.h"
#include"HP_bar.h"
#include<string>
#include"Effect_Power.h"
#include"DeadLane.h"
#include"Rhino_bullet.h"
#include"HP_Boss.h"
#include "Byte_bullet.h"

void Map::init(const char* tileSheetPath, const char* objectsPath, const char* quadtreePath)
{
	TileMap::init(tileSheetPath, objectsPath);
	quadtree.init(quadtreePath, objects);
	doors = new Door*[4];
	//neu doors sai id luc' dau la -3
	//doors[0] = new Door(3575, 376, 16, 48);
	doors[0] = new Door(261, 391, 16, 48);
	doors[0]->id = -2;
	doors[1] = new Door(3960, 376, 16, 40);
	doors[1]->id = -2;
	doors[2] = new Door(4357, 376, 16, 40);
	doors[2]->id = -2;
	doors[3] = new Door(773, 136, 16, 40);
	doors[3]->id = -2;
	
	doorCanMoves = new DoorCanMove*[2];
	doorCanMoves[0] = new DoorCanMove(502, 392, 16, 48);
	doorCanMoves[0]->id = -10;
	doorCanMoves[1] = new DoorCanMove(1014, 136, 16, 48);
	doorCanMoves[1]->id = -10;
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
	{
		Stage::curStage = stages[0];
		Stage::curStage->index = 0;
	}
}
void Map::update()
{
	for (int i = 0; i < stages.size(); i++)
	{
		if (Stage::curStage->index == i) continue;
		if (COLLISION->AABBCheck(*ROCKMAN, *stages[i]) && !ROCKMAN->onAreaBoss) //dung pahi
		{
			ROCKMAN->dx = ROCKMAN->direction;
			ROCKMAN->dy = 0;
			Stage::curStage = stages[i];
			Stage::curStage->updating = true;
			ROCKMAN->pauseAnimation = true;
		}
	}
	CAMERA->update();
	quadtree.update();
	ROCKMAN->update();

	if (CAMERA->x > Stage::curStage->x)
	{
		Stage::updating = false;
		ROCKMAN->pauseAnimation = false;
	}

	List<BaseObject*>& groundsObject = CAMERA->objectsInCamera.grounds;
	List<Enermy*>& enermyObject = CAMERA->objectsInCamera.enermies;
	List<BaseObject*>& itemsObject = CAMERA->objectsInCamera.items;
	List<BaseObject*>& trapsObject = CAMERA->objectsInCamera.traps;
	List<BaseObject*>& preventcameraObject = CAMERA->objectsInCamera.preventMoveCameras;


	#pragma region Update
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
		/*for (int i = 0; i < enermyObject.size(); i++)
		{
			COLLISION->checkCollision(bullet, enermyObject[i]);
		}*/
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
	for (int i = 0; i < RHINO_BULLET->size(); i++)
	{
		RHINO_BULLET->at(i)->update();
		//RHINO_BULLET->at(i)->updateLocation();
	}
	for (int i = 0; i < BYTE_BULLET->size(); i++)
	{
		BYTE_BULLET->at(i)->update();
	}
	for (List<RockButlet*>::Node* p = ROCKBUTLET->pHead; p; p = p->pNext)
	{
		RockButlet* bullet = p->m_value;
		//bullet->updateLocation();
	}

	for (int i = 0; i < 2; i++)
		doorCanMoves[i]->update();
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
	
	for (int i = 0; i < preventcameraObject.size(); i++)
	{
		COLLISION->checkCollision(CAMERA, preventcameraObject[i]);
	}
	for (int i = 0; i < enermyObject.size(); i++)
	{
		COLLISION->checkCollision(ROCKMAN, enermyObject[i]);
		for (int j = 0; j < groundsObject.size(); j++)
			COLLISION->checkCollision(enermyObject[i], groundsObject[j]);
		for (int j1 = 0; j1 < 4; j1++)
			COLLISION->checkCollision(enermyObject[i], doors[j1]);
		//checkCollision voi door can move
		for (int j2 = 0; j2 < 2; j2++)
			COLLISION->checkCollision(enermyObject[i], doorCanMoves[j2]);
		enermyObject[i]->updateLocation();
	}
	for (List<RockButlet*>::Node* p = ROCKBUTLET->pHead; p; p = p->pNext)
	{
		RockButlet* bullet = p->m_value;
		for (int i = 0; i < enermyObject.size(); i++)
		{
			COLLISION->checkCollision(bullet, enermyObject[i]);
		}
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
	for (int i = 0; i < RHINO_BULLET->size(); i++)
	{
		COLLISION->checkCollision(ROCKMAN, RHINO_BULLET->at(i));
	}
	for (int i = 0; i < BYTE_BULLET->size(); i++)
	{
		COLLISION->checkCollision(ROCKMAN, BYTE_BULLET->at(i));
	}
	int doorIsOpen = -1;
	for (int i = 0; i < 4; i++)
	{
		doors[i]->update();
	}
	for (int i = 0; i < 4; i++)
	{
		/*if (COLLISION->AABBCheck(*doors[i], *ROCKMAN) && !ROCKMAN->onAreaBoss)
		{
			
			doorIsOpen = i;
			if (ROCKMAN->direction == Right && ROCKMAN->x < doors[doorIsOpen]->right())
			{
				
				if (!doors[doorIsOpen]->isOpen)
				{
					ROCKMAN->dx = 0;
					doors[doorIsOpen]->Open();
					CAMERA->dx = 2 * ROCKMAN->direction;
					ROCKMAN->pauseAnimation = true;
				}
				else
				{
					doors[doorIsOpen]->isOpen = true;
					ROCKMAN->x -= ROCKMAN->dx;
				}
			}
		}
		else if(!doors[i]->isClose && ROCKMAN->x>doors[i]->right() && ROCKMAN->direction != Left && !doors[i]->isOpen)
		{
			doors[i]->Close();
			doors[i]->curFrame = doors[i]->sprite->animates[0].nFrame - 1;
			if (doorIsOpen >= 0)
			{
				doors[doorIsOpen]->isOpen = true;
			}
		}*/
		COLLISION->checkCollision(ROCKMAN, doors[i]);
		//COLLISION->AABBCheck(*ROCKMAN, *doors[i]);
	}

	for (int i = 0; i < trapsObject.size(); i++)
	{
		COLLISION->checkCollision(ROCKMAN, trapsObject[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		COLLISION->checkCollision(doorCanMoves[i], ROCKMAN);
		for (int i1 = 0; i1 < enermyObject.size(); i1++)
		{
			COLLISION->checkCollision(enermyObject[i1], doorCanMoves[i]);
		}
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
	for (int i = 0; i < RHINO_BULLET->size(); i++)
	{
		RHINO_BULLET->at(i)->updateLocation();
		if ((!COLLISION->AABBCheck(*RHINO_BULLET->at(i),*CAMERA)|| RHINO_BULLET->at(i)->allowDelete))
		{
			Rhino_bullet* rb = RHINO_BULLET->at(i);
			RHINO_BULLET->_Remove(rb);
			delete rb;
		}
	}
	for (int i = 0; i < BYTE_BULLET->size(); i++)
	{
		BYTE_BULLET->at(i)->updateLocation();
		if ((!COLLISION->AABBCheck(*BYTE_BULLET->at(i), *CAMERA) || BYTE_BULLET->at(i)->allowDelete))
		{
			Byte_bullet* bb = BYTE_BULLET->at(i);
			BYTE_BULLET->_Remove(bb);
			delete bb;
		}
	}
#pragma endregion

	HP_BAR->update();
	HP_BOSS->update();
	ROCKMAN->updateLocation();
	CAMERA->updateLocation();
	HP_BOSS->updateLocation();
	HP_BAR->updateLocation();
	updateLocation();
	
}
void Map::draw()
{
	RECT r;
	SetRect(&r, xMap, yMap, xMap+VIEWPORT_WIDTH, yMap+VIEWPORT_HEIGHT);
	tileSheetImg.RenderTexture(0, 0, &r);

	

	for (int i = 0; i < 4; i++)
	{
		doors[i]->draw();
	}
	for (int i = 0; i < 2; i++)
	{
		doorCanMoves[i]->draw();
	}
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
	HP_BAR->draw();
	HP_BOSS->draw();
	for (int i = 0; i < DRAGONFLY_BULLET->size(); i++)
	{
		DRAGONFLY_BULLET->at(i)->draw();
	}
	for (int i = 0; i < NOTOBANGER_BULLET->size(); i++)
	{
		NOTOBANGER_BULLET->at(i)->draw();
	}
	for (int i = 0; i < RHINO_BULLET->size(); i++)
	{
		RHINO_BULLET->at(i)->draw();
	}
	for (int i = 0; i < BYTE_BULLET->size(); i++)
	{
		BYTE_BULLET->at(i)->draw();
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
