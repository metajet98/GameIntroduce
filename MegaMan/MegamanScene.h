#pragma once
#include"Scene.h"
#include"Rockman.h"
#include"Map.h"
#include"HP_bar.h"
class MegamanScene:public Scene
{
public:
	Map map;
	static MegamanScene *megamanScene;

	void init();
	void update();
	void draw();
	
	MegamanScene();
	~MegamanScene();
};

