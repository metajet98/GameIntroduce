#include "MainMenu.h"



void MainMenu::init()
{
	img.Init("Data\\Miscellaneous\\Backgrounds\\IntroGame.png", D3DCOLOR_XRGB(1, 1, 1));
	chooseBullet = new Sprite("Data\\Miscellaneous\\Backgrounds\\butlet.png", "Data\\Miscellaneous\\Backgrounds\\bullet_choose.txt");
	chooseMGM = new Sprite("Data\\Rockman\\rock_x3.png", "Data\\Miscellaneous\\Backgrounds\\chose.txt");
	
}

void MainMenu::update()
{
	AudioManager::getInstance()->Play(AUDIO_STARTGAME);
	AudioManager::getInstance()->StopSound(AUDIO_BOSS_DIE);
	AudioManager::getInstance()->StopSound(AUDIO_ROCK_DIE);
	if (isStart)
	{

		if (timeDraw.canCreateFrame() && timeChangeAnimation.canCreateFrame())
		{
			chooseMGM->animates[0].next(curFrameMGM);
			chooseMGM->draw(22, 130, 0, curFrameMGM);
			
			if (curFrameMGM == chooseMGM->animates[0].nFrame - 1)
			{
				if(timeChangeAnimation.isTerminated())
					curFrameMGM = 0;
				
				isDraw = true;
			}
		}
		if (timeDraw.isTerminated())
		{
			Scene::changeScene(new MegamanScene());
			//stage
			Map::curMap->xMap = X_MAP;
			Map::curMap->yMap = Y_MAP;
			CAMERA->x = Map::curMap->xMap;
			CAMERA->y = Map::curMap->yMap;
			//sound
			AudioManager::getInstance()->StopSound(AUDIO_STARTGAME);
			AudioManager::getInstance()->LoopSound(AUDIO_FIRSTSTAGE);
		}
	}

	if (KEYBOARD->IsKeyDown(DIK_RETURN))
		isStart = true;
}

void MainMenu::updateFrame(int curFrame,Sprite* s)
{
	if (curFrame == s->animates[0].nFrame - 1)
	{
		curFrame = 0;
	}
	else s->animates[0].next(curFrame);
}

void MainMenu::draw()
{
	RECT r;
	SetRect(&r, 0, 0, 800, 600);
	img.RenderTexture(0,0,&r);

	chooseMGM->draw(22, 128, 0, curFrameMGM);
	if (isDraw)
	{
		chooseBullet->animates[0].next(curFrameBULLET);
		chooseBullet->draw(x += 7, y, 0, curFrameBULLET);
		if (curFrameBULLET == chooseBullet->animates[0].nFrame - 1)
		{
			curFrameBULLET = 0;
		}
	}
}

MainMenu::MainMenu()
{
	isDraw = false;
	isStart = false;
	curFrameMGM = 0;
	curFrameBULLET = 0;
	timeDraw.init(0.3, 5);
	timeDraw.start();
	timeChangeAnimation.init(0.2, 3);
	timeChangeAnimation.start();
	x = 50;
	y = 128;
	
}


MainMenu::~MainMenu()
{
}
