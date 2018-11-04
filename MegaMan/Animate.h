#pragma once
#include"RectF.h"
#include"GameTime.h"
#include<fstream>
using namespace std;

class Animate
{
public:
	RectF* frames;
	int nFrame;

	void init(fstream &fs);
	void next(int &curFrame);
	Animate();
	~Animate();
};

