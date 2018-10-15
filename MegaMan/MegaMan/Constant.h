#pragma once
#define CLASS_NAME "FrameWork"
#define TITLE_STR "Frame"

#define ANIMATE_DELAY_TIME_DEFAULT	0.1f
#define SCREEN_WIDTH		800
#define SCREEN_HEIGHT		600
#define VIEWPORT_WIDTH		190
#define VIEWPORT_HEIGHT		141
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
#define TIMEJUMP			160.0f/GRAVITY
#define CAMERA				Camera::getInstance()
#define X_MAP				50
#define Y_MAP				603
#define CURSCENE			MegamanScene::curScene
#define CONTROLSPRITE		ControlAnimation::getInstance()

#define FRAME_RATE			(20.0f)  // Số frame load trên một giây (frame/giây)
#define MIN_FRAME_RATE		(20.0f)
#define MIN_FRAME_TIME		(1.0f/FRAME_RATE)	// thời gian load một frame (giây/frame)
#define MAX_FRAME_TIME		(1.0f/MIN_FRAME_TIME)

#define ROCKMAN				Rockman::getInstance()
#define ROCKMAN_VX_GO		75

enum ROCK_ACTION
{
	MOVE = 0,
	STAND = 1,
	JUMP = 2,
	APPEAR = 3,
	SHOT = 4,
	STRONG_SHOT = 5,
	SLIDING = 6,
	RUN_SHOT=7
};
enum TOTAL_FRAME
{
	TF_JUMP = 11,
	TF_STAND = 1,
	TF_APPEAR = 17,
	TF_MOVE = 16,
	TF_SHOT = 8,
	TF_STRONGSHOT = 8,
	TF_SLIDING = 8,
	TF_RUN_SHOT = 32
};
enum Direction
{
	Left = -1,
	Right = 1
};
enum COLLISION_TYPE
{
	CT_GROUND,
	CT_PREVENTMOVECAMERA
};
enum BULLET_TYPE
{
	ST_FIRE,
	ST_FROZEN,
};
enum SPRITE_OBJECT
{
	SPR_MAIN,
	SPR_COUNT,
};

