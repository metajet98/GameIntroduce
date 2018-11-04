#include "Caterkiller_bullet.h"

List<Caterkiller_bullet*>* Caterkiller_bullet::caterkiller_bullet = 0;

List<Caterkiller_bullet*>* Caterkiller_bullet::getListCaterkiller_bullet()
{
	if (caterkiller_bullet == 0)
		caterkiller_bullet = new List<Caterkiller_bullet*>();
	return caterkiller_bullet;
}

void Caterkiller_bullet::update()
{
	if (above)
	{
		vx = -direction * 50;
		vy = -abs(direction) * 30;
	}
	if (!above)
	{
		vx = direction * 50;
		vy = abs(direction) * 30;
	}
		
	MovableObject::update();
}

void Caterkiller_bullet::draw()
{
	int xInViewport, yInViewport;
	TileMap::curMap->convertToViewportPos(this->x, this->y, xInViewport, yInViewport);
	int trucQuay = xInViewport + width / 2;

	/*if (direction != sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		mt._41 = 2 * trucQuay;
		mt._11 = -1;
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}*/

	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);

	/*if (direction != sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}*/
}

void Caterkiller_bullet::onCollision(BaseObject * S, int nx, int ny)
{
}

void Caterkiller_bullet::onAABBCheck(BaseObject * other)
{
	if (other == ROCKMAN && !ROCKMAN->onHit && !ROCKMAN->invisible)
	{
		ROCKMAN->changeAction(ON_HIT);
		ROCKMAN->setOnHit(true);
		this->allowDelete = true;
		ROCKMAN->gameTimeLoop.start();
	}
}

Caterkiller_bullet::Caterkiller_bullet(int xCater, int yCater, Direction directionCater,bool _above)
{
	ay = 0;
	sprite = SPRITEMANAGER->sprites[SPR_CATERKILLER_BULLET];
	direction = directionCater;
	curAnimation = 0;
	curFrame = 0;
	width = 26;
	height = 26;
	collisionType = CT_BULLET_ENERMY;
	this->x = xCater;
	this->y = yCater;
	above = _above;
	delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 2;
	delayAnimation.maxFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 3;
	timeShot.init(0.1, 1);
	timeShot.start();
}

Caterkiller_bullet::Caterkiller_bullet()
{
}


Caterkiller_bullet::~Caterkiller_bullet()
{
}
