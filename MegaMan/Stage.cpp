#include "Stage.h"
#include"Map.h"

List<Stage*>* Stage::curStages = 0;
Stage* Stage::curStage = 0;

Stage::Stage(fstream & fs, int index)
{
	fs >> x >> y >> width >> height;
	this->index = index;
	updating = false;
}

bool Stage::update()
{
	if (!updating)
		return false;
}

bool Stage::checkMegamanInStage(RectF * M, RectF * S)
{
	return (((M->left() <= S->right() && M->right() >= S->left()) &&
			(M->yCenter()<=S->top() && M->yCenter()>=S->bottom())));
}


Stage::~Stage()
{
}
