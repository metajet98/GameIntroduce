#include "SpriteManager.h"


SpriteManager*SpriteManager::instance = 0;

SpriteManager * SpriteManager::getInstance()
{
	if (instance == 0)
		instance = new SpriteManager();
	return instance;
}

SpriteManager::SpriteManager()
{
	sprites = new Sprite*[SPR_COUNT];
	sprites[SPR_MAIN] = new Sprite("Data\\Rockman\\rock_x3.png", "Data\\Rockman\\rockman.txt");
	sprites[SPR_BUTLET] = new Sprite("Data\\Rockman\\butlet.png", "Data\\Rockman\\butlet.txt");
	sprites[SPR_BULLET_STRONG] = new Sprite("Data\\Miscellaneous\\effect_megaman.png","Data\\Miscellaneous\\effect_megaman.txt");
	sprites[SPR_ROCK_DIE] = new Sprite("Data\\Rockman\\die.png", "Data\\Rockman\\die.txt");
	sprites[SPR_HP_BAR_MGM] = new Sprite("Data\\Rockman\\HP_bar_MGM.png","Data\\Rockman\\HP_bar_MGM.txt");

	sprites[SPR_DRAGONFLY] = new Sprite("Data\\Enermies\\butterfly\\butterlift.png", "Data\\Enermies\\butterfly\\butterlift.txt");
	sprites[SPR_DRAGONFLY_BULLET] = new Sprite("Data\\Enermies\\butterfly\\butterlift.png", "Data\\Enermies\\butterfly\\butterfly_bullet.txt");

	sprites[SPR_NOTORBANGER] = new Sprite("Data\\Enermies\\notorbanger\\notorbanger.png", "Data\\Enermies\\notorbanger\\notorbanger.txt");
	sprites[SPR_NOTORBANGER_BULLET] = new Sprite("Data\\Enermies\\notorbanger\\notorbanger.png", "Data\\Enermies\\notorbanger\\notorbanger_bullet.txt");

	sprites[SPR_CATERKILLER] = new Sprite("Data\\Enermies\\caterkiller\\caterkiller.png", "Data\\Enermies\\caterkiller\\caterkiller.txt");
	sprites[SPR_CATERKILLER_BULLET] = new Sprite("Data\\Enermies\\caterkiller\\caterkiller.png", "Data\\Enermies\\caterkiller\\caterkiller_bullet.txt");

	sprites[SPR_ENEMY_DIE] = new Sprite("Data\\Miscellaneous\\x3_explosions.png", "Data\\Miscellaneous\\enemy_die.txt");

	sprites[SPR_RHINO] = new Sprite("Data\\BOSS\\tunnelrhino.png", "Data\\BOSS\\rhino.txt");
	sprites[SPR_RHINO_BULLET] = new Sprite("Data\\BOSS\\tunnelrhino.png", "Data\\BOSS\\rhino_bullet.txt");
	sprites[SPR_BOSS_DIE] = new Sprite("Data\\Miscellaneous\\x3_explosions.png", "Data\\Miscellaneous\\boss_die.txt");
	sprites[SPR_HP_BAR_BOSS] = new Sprite("Data\\BOSS\\HP_bar_boss.png", "Data\\BOSS\\HP_bar_boss.txt");
	
	sprites[SPR_BIG_HEALTH] = new Sprite("Data\\Miscellaneous\\GameObject\\Items\\items.png", "Data\\Miscellaneous\\GameObject\\Items\\big_health.txt");
	sprites[SPR_SMALL_HEALTH] = new Sprite("Data\\Miscellaneous\\GameObject\\Items\\items.png", "Data\\Miscellaneous\\GameObject\\Items\\small_health.txt");
	sprites[SPR_DOOR] = new Sprite("Data\\Miscellaneous\\door.png", "Data\\Miscellaneous\\door.txt");

	sprites[SPR_GENJIBO] = new Sprite("Data\\SubBoss\\genjibo.png", "Data\\SubBoss\\genjiboCopy.txt");
	sprites[SPR_GENJIBO_SP] = new Sprite("Data\\SubBoss\\genjibo.png", "Data\\SubBoss\\genjibo_sp.txt");

	sprites[SPR_BYTE] = new Sprite("Data\\SubBoss\\byte.png", "Data\\SubBoss\\byte.txt");
	sprites[SPR_BYTE_BULLET] = new Sprite("Data\\SubBoss\\byte.png", "Data\\SubBoss\\byte_bullet.txt");

	sprites[SPR_DOOR_CAN_MOVE] = new Sprite("Data\\Miscellaneous\\doorCanMove.png", "Data\\Miscellaneous\\doorCanMove.txt");
}


SpriteManager::~SpriteManager()
{
	for (int i = 0; i < SPR_COUNT; i++)
	{
		delete[] sprites[i]->animates;
		delete sprites[i];
	}
}
