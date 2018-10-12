#include "Animate.h"



void Animate::init(fstream & fs)
{
	int id;
	fs >> id >> nFrame;

	frames = new RectF[nFrame];
	for (int i = 0; i < nFrame; i++)
	{
		fs >> frames[i].x;
		fs >> frames[i].y;
		fs >> frames[i].width;
		fs >> frames[i].height;
	}
}

void Animate::next(int & curFrame)
{
	curFrame = (curFrame + 1) % nFrame;
}

Animate::Animate()
{
}


Animate::~Animate()
{
	delete[]frames;
}
