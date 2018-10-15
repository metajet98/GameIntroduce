#include "KeyGame.h"


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
	keyUp = key->IsKeyDown(DIK_UP);
	keyDown = key->IsKeyDown(DIK_DOWN);
	keyLeft = key->IsKeyDown(DIK_LEFT);
	keyRight = key->IsKeyDown(DIK_RIGHT);

	keyJum = key->IsKeyDown(DIK_SPACE);
	keyJumpPress = keyJum && !isKeyJumpDownPrevious;
	isKeyJumpDownPrevious = keyJum;

	keySlide = key->IsKeyDown(DIK_X);

	keyJumpShot = keyJum && keyAttack;
	keyMove = keyLeft || keyRight;
}
KeyGame::KeyGame()
{
	key = KEYBOARD;
	isKeyJumpDownPrevious = false;
}


KeyGame::~KeyGame()
{
}
