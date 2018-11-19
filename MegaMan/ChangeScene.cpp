#include "ChangeScene.h"



void ChangeScene::update()
{
	/*if (gameTimeLoop.canCreateFrame())
	{
		ROCKMAN->NumberOfLife--;
		ROCKMAN->life = 24;
		ROCKMAN->onAreaBoss = false;
		ROCKMAN->alive = true;
		Scene::curScene = MegamanScene::megamanScene;

		((Map*)Map::curMap)->restoreAllObject();

		if (Stage::curStage->index == 0)
		{

		}
	}*/
}

ChangeScene::ChangeScene()
{
	gameTimeLoop.init(1, 1);
	gameTimeLoop.start();
}


ChangeScene::~ChangeScene()
{
}
