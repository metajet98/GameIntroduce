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
	keyUp = key->IsKeyDown(DIK_UP) || key->IsKeyDown(DIK_W);
	keyDown = key->IsKeyDown(DIK_DOWN) || key->IsKeyDown(DIK_S);
	keyLeft = key->IsKeyDown(DIK_LEFT) || key->IsKeyDown(DIK_A);
	keyRight = key->IsKeyDown(DIK_RIGHT) || key->IsKeyDown(DIK_D);
	keyJum = key->IsKeyDown(DIK_SPACE);
	keyAttack = key->IsKeyDown(DIK_Z);
	keyMove = keyLeft || keyRight;
}
KeyGame::KeyGame()
{
	key = KEYBOARD;

}


KeyGame::~KeyGame()
{
}
