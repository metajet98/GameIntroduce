#pragma once
#define CLASS_NAME "Megaman"
#define TITLE_STR "Game Megaman"

#define ANIMATE_DELAY_TIME_DEFAULT	0.1f
#define SCREEN_WIDTH		800
#define SCREEN_HEIGHT		600
#define VIEWPORT_WIDTH		250
#define VIEWPORT_HEIGHT		150
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
#define TIMEJUMP			60.0f/GRAVITY
#define CAMERA				Camera::getInstance()
//#define X_MAP				50
//#define Y_MAP				603
#define X_MAP				600
#define Y_MAP				80
#define CURSCENE			MegamanScene::curScene
#define CONTROLSPRITE		ControlAnimation::getInstance()

#define FRAME_RATE			(20.0f)  // Số frame load trên một giây (frame/giây)
#define MIN_FRAME_RATE		(20.0f)
#define MIN_FRAME_TIME		(1.0f/FRAME_RATE)	// thời gian load một frame (giây/frame)
#define MAX_FRAME_TIME		(1.0f/MIN_FRAME_TIME)

#define ROCKMAN				Rockman::getInstance()
#define ROCKMAN_VX_GO		75
#define ROCKBUTLET			RockButlet::getListBullet()
#define HP_BAR				HP_bar::getInstance()

#define DRAGONFLY			Dragonfly::getInstance()
#define DRAGONFLY_BULLET	Dragonfly_bullet::getListDragonfly_bullet()

#define NOTOBANGER			NotorBanger::getInstance()
#define NOTOBANGER_BULLET	NotoBanger_bullet::getListnotobanger_bullet()

#define CATERKILLER			Caterkiller::getInstance()
#define CATERKILLER_BULLET	Caterkiller_bullet::getListCaterkiller_bullet()

enum ROCK_ACTION
{
	APPEAR = 0,
	STAND = 9,
	MOVE = 1,
	JUMP = 2,
	SHOT = 3,
	RUN_SHOT = 4,
	PUSHING = 5,
	JUMP_SHOT = 6,
	PUSHING_SHOT = 7,
	SLIDING = 8,
	PUSHING_JUMP = 10,
	ON_HIT=11,
	DIE = 12,
	HIGH_JUMP = 13,
};
enum Direction
{
	Left = -1,
	Right = 1
};
enum COLLISION_TYPE
{
	CT_GROUND,
	CT_PREVENTMOVECAMERA,
	CT_BUTLET,
	CT_ENERMY,
	CT_PLAYER,
	CT_BULLET_ENERMY,
	CT_NONE,
};
enum SPRITE_OBJECT
{
	SPR_MAIN,
	SPR_BUTLET,
	SPR_DRAGONFLY,
	SPR_DRAGONFLY_BULLET,
	SPR_NOTORBANGER,
	SPR_NOTORBANGER_BULLET,
	SPR_ENEMY_DIE,
	SPR_BOSS_DIE,
	SPR_ROCK_DIE,
	SPR_CATERKILLER,
	SPR_CATERKILLER_BULLET,
	SPR_HP_BAR_MGM,
	SPR_HP_BAR_BOSS,
	SPR_COUNT
};
enum CATEGORY_ENEMY
{
	CREP_DRAGONFLY,
	CREP_NOTORBANGER
};
enum CATEGORY_BULLET_FOR_MEGAMAN {
	OF_MEGAMAN,
};

