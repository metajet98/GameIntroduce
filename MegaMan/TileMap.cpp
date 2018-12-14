#include "TileMap.h"
#include"Camera.h"
#include"Dragonfly.h"
#include "NotorBanger.h"
#include"Caterkiller.h"
#include"BigHealth.h"
#include"SmallHealth.h"
#include "DeadLane.h"
#include"Rhino.h"
#include "Genjibo.h"
#include "Byte.h"

TileMap* TileMap::curMap = 0;
TileMap::TileMap()
{
	curMap = this;
}
void TileMap::convertToViewportPos(int xInMap, int yInMap, int & xViewport, int & yViewport)
{
	D3DXVECTOR3 posInMap;
	D3DXVECTOR4 posViewport;
	D3DXMATRIX mt;

	D3DXMatrixIdentity(&mt);
	mt._41 = -(int)xMap;
	mt._42 = -(int)yMap;

	posInMap.x = xInMap;
	posInMap.y = yInMap;
	posInMap.z = 0;

	D3DXVec3Transform(&posViewport, &posInMap, &mt);
	xViewport = posViewport.x;
	yViewport = posViewport.y;
}
void TileMap::updateLocation()
{
	xMap += CAMERA->dx;
	yMap += CAMERA->dy;
}
void TileMap::initObjects(const char* objectsPath)
{
	fstream fs(objectsPath);
	fs >> nObjects;
	int id;
	float x, y, width, height;

	objects = new BaseObject*[nObjects];

	for (int i = 0; i < nObjects; i++)
	{
		fs >> id >> x >> y >> width >> height;
		switch (id % 100) //
		{
		case SPR_DRAGONFLY:

			objects[i] = new Dragonfly();
			break;
		case SPR_NOTORBANGER:
			objects[i] = new NotorBanger();
			break;
		case SPR_CATERKILLER:
			int diretion;
			fs >> diretion;
			switch (diretion)
			{
			case 1:
				diretion = 1;
				break;
			default: 
				diretion = -1;
				break;
			}
			objects[i] = new Caterkiller(diretion);
			break;
		case SPR_BIG_HEALTH:
			objects[i] = new BigHealth();
			break;
		case SPR_SMALL_HEALTH:
			objects[i] = new SmallHealth();
			break;
		case SPR_RHINO:
			objects[i] = new Rhino();
			break;
		case -5: //Deadlane
			objects[i] = new DeadLane();
			break;
		case -3:
			objects[i] = new BaseObject();
			objects[i]->collisionType = CT_PREVENTMOVECAMERA;
			break;
		case SPR_GENJIBO:
	 		objects[i] = new Genjibo();
			break;
		case SPR_BYTE:
			objects[i] = new Byte();
			break;
		default:
			objects[i] = new BaseObject();
			break;
		}
		objects[i]->id = id;
		objects[i]->x = x;
		objects[i]->y = y;
		objects[i]->width = width;
		objects[i]->height = height;

		objects[i]->getFromObject(objects[i]);
	}

}
void TileMap::init(const char * tileSheetPath, const char* objectsPath)
{
	tileSheetImg.Init(tileSheetPath, D3DCOLOR_XRGB(0, 0, 0));
	initObjects(objectsPath);
}

TileMap::~TileMap()
{

}
