#pragma once
#define CLASS_NAME "Megaman"
#define TITLE_STR "Game Megaman"

#define ANIMATE_DELAY_TIME_DEFAULT	0.08f
#define SCREEN_WIDTH		800
#define SCREEN_HEIGHT		600
#define VIEWPORT_WIDTH		255
#define VIEWPORT_HEIGHT		230
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
#define X_MAP				7
#define Y_MAP				530
//#define X_MAP				1544
//#define Y_MAP				519
//#define X_MAP				3946
//#define Y_MAP				282
#define CURSCENE			MegamanScene::curScene
#define CONTROLSPRITE		ControlAnimation::getInstance()

#define FRAME_RATE			(40.0f)  // Số frame load trên một giây (frame/giây)
#define MIN_FRAME_RATE		(40.0f)
#define MIN_FRAME_TIME		(1.0f/FRAME_RATE)	// thời gian load một frame (giây/frame)
#define MAX_FRAME_TIME		(1.0f/MIN_FRAME_TIME)

#define ROCKMAN				Rockman::getInstance()
#define ROCKMAN_VX_GO		75
#define ROCKBUTLET			RockButlet::getListBullet()
#define EFFECT_POWER		Effect_Power::getInstance()
#define HP_BAR				HP_bar::getInstance()

#define DRAGONFLY			Dragonfly::getInstance()
#define DRAGONFLY_BULLET	Dragonfly_bullet::getListDragonfly_bullet()

#define NOTOBANGER			NotorBanger::getInstance()
#define NOTOBANGER_BULLET	NotoBanger_bullet::getListnotobanger_bullet()

#define CATERKILLER			Caterkiller::getInstance()
#define CATERKILLER_BULLET	Caterkiller_bullet::getListCaterkiller_bullet()

#define RHINO				Rhino::getInstance()
#define RHINO_BULLET		Rhino_bullet::getListBossBullet()
#define HP_BOSS				HP_Boss::getInstance()

#define GENJIBO				Genjibo::getInstance()
#define LIFE_GENJIBO		24
#define GENJIBO_SP			Genjibo_sp::getInstance()

#define BOSS_BYTE			Byte::getInstance()
#define BYTE_BULLET			Byte_bullet::getInstance()
#define LIFE_BYTE			18

#define BLASHHORNET			BlashHornet::getInstance()
#define BLASHHORNET_WING	BlashHornet_Wing::getInstance()
#define BLASHHORNET_Life	24 // (curLife / totalLife) * 24
#define HORNET				Hornet::getInstance()
#define BLASHHORNET_POINT	BlashHornet_Point::getInstance()
#define BLASHHORNET_VY		70



enum ROCK_ACTION
{
	APPEAR = 0,
	MOVE = 1,
	JUMP = 2,
	SHOT = 3,
	RUN_SHOT = 4,
	PUSHING = 5,
	JUMP_SHOT = 6,
	PUSHING_SHOT = 7,
	SLIDING = 8,
	STAND = 9,
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
	CT_BUTTLET_STRONG,
	CT_ENERMY,
	CT_PLAYER,
	CT_BULLET_ENERMY,
	CT_ITEM,
	CT_DOOR,
	CT_DEAD_LANE,
	CT_DOOR_CAN_MOVE,
	CT_FOLLOWING,
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
	SPR_BIG_HEALTH,
	SPR_SMALL_HEALTH,
	SPR_DOOR,
	SPR_RHINO,
	SPR_BULLET_STRONG,
	SPR_RHINO_BULLET,
	SPR_GENJIBO,
	SPR_BYTE,
	SPR_BYTE_BULLET,
	SPR_DOOR_CAN_MOVE,
	SPR_GENJIBO_SP,
	SPR_BLASHHORNET,
	SPR_HORNET,
	SPR_BLASHHORNET_WING,
	SPR_BLASHHORNET_POINT,
	SPR_HORNET_DIE,
	SPR_COUNT
};
enum CATEGORY_ENEMY
{
	CREP_DRAGONFLY,
	CREP_NOTORBANGER
};
enum CATEGORY_BULLET_FOR_MEGAMAN {
	OF_MEGAMAN,
	OF_STRONG_MEGAMAN,
	OF_STRONG_2_MEGAMAN,
};

