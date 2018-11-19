#include "Stage.h"
#include"Map.h"

List<Stage*>* Stage::curStages = 0;
Stage* Stage::curStage = 0;
bool Stage::updating = false;

Stage::Stage(fstream & fs, int index)
{
	fs >> x >> y >> width >> height >> xPre >> yPre;
	this->index = index;

}

bool Stage::update()
{
	if (!updating)
		return false;
}

void Stage::next()
{
	//curStage = curStages->at(curStage->index + 1);
}

void Stage::prev()
{
	Map::curMap->xMap = xPre;
	Map::curMap->yMap = yPre;
	CAMERA->x = xPre;
	CAMERA->y = yPre;
	CAMERA->dx = 0;
	CAMERA->dy = 0;
}

bool Stage::checkMegamanInStage(RectF * M, RectF * S)
{
	return (((M->left() <= S->right() && M->right() >= S->left()) &&
			(M->yCenter()<=S->top() && M->yCenter()>=S->bottom())));
}


Stage::~Stage()
{
}
