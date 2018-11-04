#include "Stage.h"
#include"Map.h"

List<Stage*>* Stage::curStages = 0;
Stage* Stage::curStage = 0;

Stage::Stage(fstream & fs, int index)
{
	fs >> x >> y >> width >> height >> xViewportNext >> yViewportNext >> xViewportPrev >> yViewportPrev;
	this->index = index;
	updating = false;
}

void Stage::loadStageNext()
{
	Map::curMap->xMap = -xViewportNext;
	Map::curMap->yMap = -yViewportNext;
	CAMERA->x = xViewportNext;
	CAMERA->y = yViewportNext;
	CAMERA->dx = 0;
	CAMERA->dy = 0;
}

void Stage::loadStagePrev()
{
	Map::curMap->xMap = -xViewportPrev;
	Map::curMap->yMap = -yViewportPrev;
	CAMERA->x = xViewportPrev;
	CAMERA->y = yViewportPrev;
	CAMERA->dx = 0;
	CAMERA->dy = 0;
}

bool Stage::update()
{
	if (!updating)
		return false;
}

void Stage::next()
{
	curStage = curStages->at(curStage->index + 1);
	curStage->loadStageNext();
}

void Stage::prev()
{
	curStage = curStages->at(curStage->index - 1);
	curStage->loadStagePrev();
}

void Stage::onStageChange(Stage * nextStage)
{
}



Stage::~Stage()
{
}
