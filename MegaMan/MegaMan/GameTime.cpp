#include "GameTime.h"


GameTime*GameTime::instance = 0;
GameTime * GameTime::getInstance()
{
	if (instance == 0)
		instance = new GameTime();
	return instance;
}

bool GameTime::canCreateFrame()
{
	QueryPerformanceCounter(&timeEnd);
	frameTime = (float)(timeEnd.QuadPart - timeStart.QuadPart) / (float)(timeFreq.QuadPart);

	if (frameTime < minFrameTime)
		return false;

	if (frameTime > maxFrameTime)
		frameTime = maxFrameTime;

	timeStart = timeEnd;

	return true;
}

GameTime::GameTime()
{
	QueryPerformanceFrequency(&timeFreq);
	QueryPerformanceCounter(&timeStart);
}


GameTime::~GameTime()
{
}
