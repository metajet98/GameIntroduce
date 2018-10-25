#include "MegamanScene.h"
#include"RockButlet.h"
#include"TileMap.h"

MegamanScene* MegamanScene::megamanScene;

void MegamanScene::init()
{
	map.init("Data\\Map\\Stage3.png", "Data\\Map\\Stage3(objectMap).txt", "Data\\Map\\Stage3(QuadTree).txt");
}

void MegamanScene::update()
{
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
