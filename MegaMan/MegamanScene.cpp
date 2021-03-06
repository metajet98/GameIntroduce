#include "MegamanScene.h"
#include"RockButlet.h"
#include"TileMap.h"
#include"MainMenu.h"

MegamanScene* MegamanScene::megamanScene;

void MegamanScene::init()
{
	map.init("Data\\Map\\Stage3.png", "Data\\Map\\objectsMap-genjibo.txt", "Data\\Map\\quadtree.txt");
	//Stage3(QuadTree)
	//quadtree
	map.initStage("Data\\Map\\changestage.txt");
}

void MegamanScene::update()
{
	if (ROCKMAN->NumberOfLife==0 || BLASHHORNET->isDeath) //boss die
	{
		for (int i = 0; i < CAMERA->objectsInCamera.allObjects.size(); i++)
		{
			BaseObject* obj = CAMERA->objectsInCamera.allObjects[i];
			CAMERA->objectsInCamera.remove(obj);
			i--;
		}
		DoorCanMove::getInstance()->Clear();
		Scene::changeScene(new MainMenu());
		ROCKMAN->NumberOfLife = 3;
		ROCKMAN->x = 110;
		ROCKMAN->y = 680;
		Stage::curStage = Stage::curStages->at(0);
		Stage::curStage->prev();
		BLASHHORNET->isDeath = false;
		ROCKMAN->curAnimation = APPEAR;
		ROCKMAN->allowDraw = true;
		ROCKMAN->curFrame = 0;
		ROCKMAN->life = 24;
		ROCKMAN->onAreaBoss = false;
		ROCKMAN->onAreaBossSub = false;
		ROCKMAN->alive = true;
		ROCKMAN->pauseAnimation = false;
		ROCKMAN->isDeath = false;
		ROCKMAN->isFollowing = false;
		ROCKMAN->timeDeath.start();
		HP_BAR->x = CAMERA->x;
		HP_BAR->y = CAMERA->y;
		//HP_BOSS->curFrame = RHINO->life;
		HP_BOSS->x = CAMERA->x + 220;
		HP_BOSS->y = CAMERA->y;
		return;
	}
	if (!ROCKMAN->alive && ROCKMAN->isDeath)
	{
		ROCKMAN->curAnimation = APPEAR;
		ROCKMAN->allowDraw = true;
		ROCKMAN->curFrame = 0;
		ROCKMAN->NumberOfLife--;
		ROCKMAN->life = 24;
		ROCKMAN->onAreaBoss = false;
		ROCKMAN->onAreaBossSub = false;
		ROCKMAN->alive = true;
		ROCKMAN->pauseAnimation = false;
		ROCKMAN->isDeath = false;
		ROCKMAN->isFollowing = false;
		ROCKMAN->timeDeath.start();
		DieEffect::getList()->Clear();
		if (Stage::curStage->index == 0 || Stage::curStage->index == 1)
		{
			ROCKMAN->x = 110;
			ROCKMAN->y = 650;
			Stage::curStage = Stage::curStages->at(0);
			Stage::curStage->prev();
		}
		else if (Stage::curStage->index == 2 || Stage::curStage->index == 3)
		{
			ROCKMAN->x = 609;
			ROCKMAN->y = 408;
			Stage::curStage = Stage::curStages->at(2);
			Stage::curStage->prev();
		}
		else if (Stage::curStage->index == 4)
		{
			ROCKMAN->x = 609;
			ROCKMAN->y = 408;
			Stage::curStage = Stage::curStages->at(2);
			Stage::curStage->prev();
		}
		else if (Stage::curStage->index == 5)
		{
			ROCKMAN->x = 1055;
			ROCKMAN->y = 123;
			Stage::curStage = Stage::curStages->at(4);
			Stage::curStage->prev();
		}
		else if (Stage::curStage->index == 6 || Stage::curStage->index==7)
		{
			ROCKMAN->x = 1821;
			ROCKMAN->y =586;
			Stage::curStage = Stage::curStages->at(6);
			Stage::curStage->prev();
		}
		else if (Stage::curStage->index == 8)
		{
			ROCKMAN->x = 4017;
			ROCKMAN->y = 360;
			BLASHHORNET->restore(BLASHHORNET);
			Stage::curStage = Stage::curStages->at(7);
			Stage::curStage->prev();
		}
		HP_BAR->x = CAMERA->x;
		HP_BAR->y = CAMERA->y;
		//HP_BOSS->curFrame = RHINO->life;
		HP_BOSS->x = CAMERA->x + 220;
		HP_BOSS->y = CAMERA->y;
		if(ROCKMAN->NumberOfLife!=0)
			AudioManager::getInstance()->Play(AUDIO_FIRSTSTAGE);
		return;
	}

	map.update();
}

void MegamanScene::draw()
{
	map.draw();

	ROCKMAN->draw();
	for (List<RockButlet*>::Node* p = ROCKBUTLET->pHead; p; p = p->pNext)
	{
		RockButlet* bullet = p->m_value;
		bullet->draw();
	}
}

MegamanScene::MegamanScene()
{
	megamanScene = this;
}


MegamanScene::~MegamanScene()
{
}
