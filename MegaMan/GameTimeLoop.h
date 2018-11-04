#pragma once
#include "GameTime.h"

class GameTimeLoop : public GameTime
{

public:
	int curLoop;
	int loopCount;

	void init(float minFrameTime, int loopCount);
	void setLoopCount(int loopCount);
	bool isTerminated();
	bool canCreateFrame();
	void start();

	GameTimeLoop();
	~GameTimeLoop();
};

