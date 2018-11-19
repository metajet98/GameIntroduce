#pragma once
#include "Scene.h"
#include "GameTimeLoop.h"
#include "Rockman.h"
#include "MegamanScene.h"
class ChangeScene: public Scene
{
public:
	GameTimeLoop gameTimeLoop;
	void update();
	ChangeScene();
	~ChangeScene();
};

