#pragma once
#include "BaseObject.h"
#include "SpriteManager.h"
#include "GameTimeLoop.h"



class DrawableObject : public BaseObject
{
public:
	Sprite*sprite;
	int curAnimation;
	int nextAnimation;
	int curFrame;
	bool pauseAnimation;
	GameTime delayAnimation;
	GameTimeLoop gameTimeLoop;
	Direction direction;

	void setSprite();
	void setPauseAnimation(bool pauseAnimation, int frameIndex);
	void setPauseAnimation(bool pauseAnimation);
	virtual void changeAction(int newAction);
	virtual void update();
	virtual void draw();
	virtual void restore(BaseObject*obj);

	DrawableObject();
	~DrawableObject();
};

