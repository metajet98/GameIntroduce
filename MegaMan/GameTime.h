#pragma once
#include<Windows.h>
#include"Constant.h"

class GameTime
{
private:
	static GameTime*instance;

public:
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timeFreq;
	float minFrameTime;
	float maxFrameTime;
	static GameTime* getInstance();
	float frameTime;

	bool canCreateFrame();

	GameTime();
	~GameTime();
};

