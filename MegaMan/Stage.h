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
	static bool updating;

	int index;
	int xPre;
	int yPre;

	virtual bool update();
	void next();
	void prev();
	static bool checkMegamanInStage(RectF* M, RectF* S);// phuc vu cho viec chuyen stage
	Stage(fstream& fs, int index);
	~Stage();
};

