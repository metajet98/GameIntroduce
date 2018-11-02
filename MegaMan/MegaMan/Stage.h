#pragma once
#include "RectF.h"
#include"List.h"
#include <fstream>
using namespace std;
class Stage :public RectF
{
public:
	static List<Stage*>* curStages;
	static Stage* curStage;
	int index;
	bool updating;
	float xViewportNext, yViewportNext, xViewportPrev, yViewportPrev;

	virtual void loadStageNext();
	virtual void loadStagePrev();
	virtual bool update();
	static void next();
	static void prev();
	virtual void onStageChange(Stage* nextStage);

	Stage(fstream& fs, int index);
	~Stage();
};

