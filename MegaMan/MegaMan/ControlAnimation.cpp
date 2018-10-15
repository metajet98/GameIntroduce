#include "ControlAnimation.h"


ControlAnimation* ControlAnimation::instance = 0;
ControlAnimation * ControlAnimation::getInstance()
{
	if (instance == 0)
		instance = new ControlAnimation();
	return instance;
}

int ControlAnimation::getCountFrame(int r)
{
	if (r == JUMP) countFrame = TF_JUMP;
	if (r == STAND) countFrame = TF_STAND;
	if (r == MOVE) countFrame = TF_MOVE;
	if (r == SHOT) countFrame = TF_SHOT;
	if (r == APPEAR) countFrame = TF_APPEAR;
	if (r == STRONG_SHOT) countFrame = TF_STRONGSHOT;
	if (r == RUN_SHOT) countFrame = TF_RUN_SHOT;
	if (r == SLIDING) countFrame = TF_SLIDING;
	return countFrame;
}

void ControlAnimation::draw(Sprite *s,int x, int y, int curAnimation,int &curFrame)
{
	getCountFrame(curAnimation);
	if (curAnimation == JUMP)
		s->draw(x, y, curAnimation, ++curFrame*TIMEJUMP);
	else
	{
		s->draw(x, y, curAnimation, ++curFrame%countFrame);
	}

}

ControlAnimation::ControlAnimation()
{
	countFrame = 0;

}


ControlAnimation::~ControlAnimation()
{
}
