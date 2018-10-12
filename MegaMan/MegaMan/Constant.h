#pragma once
#define CLASS_NAME "FrameWork"
#define TITLE_STR "Frame"

#define ANIMATE_DELAY_TIME_DEFAULT	0.1f
#define SCREEN_WIDTH		640
#define SCREEN_HEIGHT		420
#define VIEWPORT_WIDTH		184
#define VIEWPORT_HEIGHT		156
#define BACK_WIDTH			VIEWPORT_WIDTH
#define BACK_HEIGHT			VIEWPORT_HEIGHT

#define WINDOW				WindowGame::getInstance()
#define GRAPHICS			Graphics::getInstance()
#define GAME_TIME			GameTime::getInstance()
#define SPRITEMANAGER		SpriteManager::getInstance()
#define COLLISION			CollisionManager::getInstance()
#define KEYBOARD			KeyBoard::getInstance()
#define KEY					KeyGame::getInstance()
#define MOUSE				Mouse::getInstance()
#define TIME				GameTime::getInstance()->frameTime
#define GRAVITY				300
#define CAMERA				Camera::getInstance()
#define X_MAP				41
#define Y_MAP				589
#define CURSCENE			MegamanScene::curScene

#define FRAME_RATE			(20.0f)  // Số frame load trên một giây (frame/giây)
#define MIN_FRAME_RATE		(20.0f)
#define MIN_FRAME_TIME		(1.0f/FRAME_RATE)	// thời gian load một frame (giây/frame)
#define MAX_FRAME_TIME		(1.0f/MIN_FRAME_TIME)

#define ROCKMAN				Rockman::getInstance()
#define ROCKMAN_VX_GO		50

enum ROCK_ACTION
{
	MOVE = 0,
	STAND = 1,
	JUMP = 2,
	APPEAR = 3,
	SHOT = 4
};
enum Direction
{
	Left = -1,
	Right = 1
};
enum COLLISION_TYPE
{
	CT_GROUND

};

