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

	bool keyJum;
	bool keyJumpPress, isKeyJumpDownPrevious;

	bool keyAttack;

	bool keyMove;
	bool keySlide;

	bool keyJumpShot;

	void update();

	KeyGame();
	~KeyGame();
};

