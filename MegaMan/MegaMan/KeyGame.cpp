#include "KeyGame.h"
#include"GameTime.h"

KeyGame*KeyGame::instance = 0;

KeyGame * KeyGame::getInstance()
{
	if (instance == 0)
		instance = new KeyGame();
	return instance;
}

void KeyGame::update()
{
	keyAttack = key->IsKeyDown(DIK_Z);
	keyAttackPress = keyAttack && !isKeyAttackDownPrevious;
	isKeyAttackDownPrevious = keyAttack;

	keyUp = key->IsKeyDown(DIK_UP);
	keyDown = key->IsKeyDown(DIK_DOWN);
	keyLeft = key->IsKeyDown(DIK_LEFT);
	keyRight = key->IsKeyDown(DIK_RIGHT);

	keyJum = key->IsKeyDown(DIK_SPACE);
	keyJumpPress = keyJum && !isKeyJumpDownPrevious;
	isKeyJumpDownPrevious = keyJum;

	keySlide = key->IsKeyDown(DIK_X);
	keySlidePress = keySlide && !isKeySlideDownPrevious;
	isKeySlideDownPrevious = keySlide;

	keyJumpShot = keyJum && keyAttack;
	keyMove = keyLeft || keyRight;

	keyRunShot = keyMove && keyAttack;

	keyStrongJump = keySlide && keyJum && keyMove;
}
KeyGame::KeyGame()
{
	key = KEYBOARD;
	isKeyJumpDownPrevious = false;
	isKeySlideDownPrevious = false;
	isKeyAttackDownPrevious = false;
}


KeyGame::~KeyGame()
{
}
