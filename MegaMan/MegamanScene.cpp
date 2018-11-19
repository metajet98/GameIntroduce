#include "MegamanScene.h"
#include"RockButlet.h"
#include"TileMap.h"

MegamanScene* MegamanScene::megamanScene;

void MegamanScene::init()
{
	map.init("Data\\Map\\Stage3.png", "Data\\Map\\objectsMap.txt", "Data\\Map\\quadtree.txt");
	//Stage3(QuadTree)
	//quadtree
	map.initStage("Data\\Map\\changestage.txt");
}

void MegamanScene::update()
{
	if (ROCKMAN->NumberOfLife==0)
	{
		//Scene gameover
		ROCKMAN->NumberOfLife = 3;
		ROCKMAN->x = 110;
		ROCKMAN->y = 680;
		Stage::curStage = Stage::curStages->at(0);
		Stage::curStage->prev();
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
		ROCKMAN->alive = true;
		if (Stage::curStage->index == 0)
		{
			ROCKMAN->x = 110;
			ROCKMAN->y = 680;
			Stage::curStage = Stage::curStages->at(0);
			Stage::curStage->prev();
		}
		else if (Stage::curStage->index == 1)
		{
			ROCKMAN->x = 609;
			ROCKMAN->y = 438;
			Stage::curStage = Stage::curStages->at(1);
			Stage::curStage->prev();
		}
		else if (Stage::curStage->index == 2)
		{
			ROCKMAN->x = 1055;
			ROCKMAN->y = 153;
			Stage::curStage = Stage::curStages->at(2);
			Stage::curStage->prev();
		}
		else if (Stage::curStage->index == 3)
		{
			ROCKMAN->x = 1566;
			ROCKMAN->y = 425;
			Stage::curStage = Stage::curStages->at(3);
			Stage::curStage->prev();
		}
		else if (Stage::curStage->index == 4)
		{
			ROCKMAN->x = 1821;
			ROCKMAN->y = 616;
			Stage::curStage = Stage::curStages->at(4);
			Stage::curStage->prev();
		}
		else if (Stage::curStage->index == 5)
		{
			ROCKMAN->x = 4017;
			ROCKMAN->y = 390;
			Stage::curStage = Stage::curStages->at(5);
			Stage::curStage->prev();
		}
		else if (Stage::curStage->index == 6)
		{
			ROCKMAN->x = 4017;
			ROCKMAN->y = 390;
			Stage::curStage = Stage::curStages->at(6);
			Stage::curStage->prev();
		}
		HP_BAR->x = CAMERA->x;
		HP_BAR->y = CAMERA->y;
		ROCKMAN->timeDeath.start();
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
