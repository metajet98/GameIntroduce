#pragma once
#include "Scene.h"
#include "KeyGame.h"
#include "Texture.h"
#include "GameTimeLoop.h"
#include "Sprite.h"
#include "Constant.h"
#include "TileMap.h"
#include "MegamanScene.h"
#include "AudioManager.h"
class MainMenu: public Scene
{
public:
	Texture img;
	Sprite* chooseMGM;
	int curFrameMGM;

	Sprite* chooseBullet;
	int curFrameBULLET;

	bool isDraw;
	GameTimeLoop timeDraw;
	bool isStart;

	GameTimeLoop timeChangeAnimation;
	int x, y;

	void init();
	void update();
	void updateFrame(int curFrame,Sprite* s);
	void draw();

	MainMenu();
	~MainMenu();
};

