#include "GameTimeLoop.h"


void GameTimeLoop::init(float minFrameTime, int loopCount)
{
	this->minFrameTime = minFrameTime;
	setLoopCount(loopCount);
	curLoop = loopCount;
}

void GameTimeLoop::setLoopCount(int loopCount)
{
	this->loopCount = loopCount;
}

bool GameTimeLoop::isTerminated()
{
	return curLoop == loopCount;
}

bool GameTimeLoop::canCreateFrame()
{
	if (!isTerminated())
	{
		if (GameTime::canCreateFrame())
		{
			curLoop++;
			return true;
		}

		return false;
	}

	return false;
}

void GameTimeLoop::start()
{
	curLoop = 0;
	QueryPerformanceCounter(&timeStart);
}

GameTimeLoop::GameTimeLoop()
{
}

GameTimeLoop::~GameTimeLoop()
{
}
