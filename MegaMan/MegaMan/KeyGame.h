#pragma once
#include"KeyBoard.h"
#include"Constant.h"


class KeyGame
{
private:
	KeyBoard* key;

	static KeyGame*instance;
public:
	static KeyGame*getInstance();

	bool keyUp;
	bool keyDown;
	bool keyLeft;
	bool keyRight;

	bool keyStrongJump;
	bool keyJum;
	bool keyJumpPress, isKeyJumpDownPrevious;

	bool keyAttack;

	bool keyMove;

	bool keySlide;
	bool keySlidePress, isKeySlideDownPrevious;

	bool keyJumpShot;

	bool keyRunShot;

	void update();

	KeyGame();
	~KeyGame();
};

