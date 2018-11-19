#include<Windows.h>
#include"Constant.h"
#include"WindowGame.h"
#include"Graphics.h"
#include"Texture.h"
#include"GameTime.h"
#include"CollisionManager.h"
#include"SpriteManager.h"
#include"KeyGame.h"
#include"KeyBoard.h"
#include"Constant.h"
#include"Mouse.h"
#include"Rockman.h"
#include"MegamanScene.h"
#include "MainMenu.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WINDOW->initHandleWindows(hInstance, nCmdShow);

	//MegamanScene::changeScene(new MegamanScene());
	MegamanScene::changeScene(new MainMenu());

	KeyBoard::Create(hInstance, WINDOW->getHandleWindow());
	GAME_TIME->minFrameTime = MIN_FRAME_TIME;
	GAME_TIME->maxFrameTime = MAX_FRAME_TIME;
	
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (GAME_TIME->canCreateFrame())
			{
				KEYBOARD->PollKeyboard();
				KEYBOARD->updateKeyBoard();
				KEY->update();

				CURSCENE->update();

				GRAPHICS->BeginGraphics();

				CURSCENE->draw();

				GRAPHICS->EndGraphics();
				GRAPHICS->PresentBackBuffer();
			}
				else
				{
					timeBeginPeriod(1);
					Sleep((DWORD)(1000 * (GAME_TIME->minFrameTime)));
					timeEndPeriod(1);
				}
		}
	}

	return nCmdShow;
}