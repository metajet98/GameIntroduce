#include "MegamanScene.h"

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
}

MegamanScene::MegamanScene()
{
	megamanScene = this;
}


MegamanScene::~MegamanScene()
{
}
