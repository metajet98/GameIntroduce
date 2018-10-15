#pragma once
#include"Rockman.h"
#include"BaseObject.h"
#include"CollisionManager.h"
#include"ObjectsCategory.h"
#include<DirectXMath.h>
class Camera:public BaseObject
{
	static Camera* instance;
public:
	static Camera* getInstance();

	ObjectsCategory objectsInCamera;
	void onCollision(BaseObject* other, int nx, int ny);
	

	void update();
	Camera();

	~Camera();
};

