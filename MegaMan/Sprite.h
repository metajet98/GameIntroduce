#pragma once
#include"Animate.h"
#include"Texture.h"

class Sprite
{

public:
	Animate*animates;
	Texture*image;
	int nAnimation;

	Sprite(const char*imageFilePath, const char*animationInfoFilePath);
	void init(const char*imageFilePath, const char*animationInfoFilePath);
	void initAnimation(const char* animationInfoFilePath);
	void draw(int x, int y, int curAnimate, int curFrame);

	Sprite();
	~Sprite();
};

