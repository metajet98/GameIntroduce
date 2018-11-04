#include "Sprite.h"



Sprite::Sprite(const char * imageFilePath, const char * animationFilePath)
{
	init(imageFilePath, animationFilePath);
}

void Sprite::init(const char * imageFilePath, const char * animationInfoFilePath)
{
	int r, g, b;
	fstream fs(animationInfoFilePath);
	fs >> r >> g >> b >> nAnimation;

	animates = new Animate[nAnimation];

	for (int i = 0; i < nAnimation; i++)
		animates[i].init(fs);
	image = new Texture(imageFilePath, D3DCOLOR_XRGB(r, g, b));

	fs.close();
}

void Sprite::initAnimation(const char * animationInfoInfoFilePath)
{
	int r, g, b;
	fstream fs(animationInfoInfoFilePath);
	fs >> r >> g >> b >> nAnimation;

	animates = new Animate[nAnimation];

	for (int i = 0; i < nAnimation; i++)
		animates[i].init(fs);

	fs.close();
}

void Sprite::draw(int x, int y, int curAnimate, int curFrame)
{
	Animate* animate = &animates[curAnimate];
	image->RenderTexture(x, y, &animate->frames[curFrame].toRECT());
}


Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}
