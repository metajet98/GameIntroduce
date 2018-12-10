#include "Byte_bullet.h"


List<Byte_bullet*>* Byte_bullet::instance = 0;
List<Byte_bullet*>* Byte_bullet::getInstance()
{
	if (instance == 0)
		instance = new List< Byte_bullet*>();
	return instance;
}

void Byte_bullet::update()
{
	vx = direction * 110;
	dx = vx * TIME;
	DrawableObject::update();
}

void Byte_bullet::draw()
{
	int xInViewport, yInViewport;
	TileMap::curMap->convertToViewportPos(this->x, this->y, xInViewport, yInViewport);
	int trucQuay = xInViewport + width / 2;

	if (direction == sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		mt._41 = 2 * trucQuay;
		mt._11 = -1;
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}

	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);

	if (direction == sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}
}

void Byte_bullet::onCollision(BaseObject * S, int nx, int ny)
{
}

void Byte_bullet::onAABBCheck(BaseObject * other)
{
	if (other == ROCKMAN && !ROCKMAN->onHit && !ROCKMAN->invisible)
	{
		ROCKMAN->changeAction(ON_HIT);
		ROCKMAN->setOnHit(true);
		ROCKMAN->life -= 1;
		this->allowDelete = true;
		ROCKMAN->gameTimeLoop.start();
	}
}

Byte_bullet::Byte_bullet()
{
}

Byte_bullet::Byte_bullet(int xByte, int yByte, Direction dir)
{
	sprite = SPRITEMANAGER->sprites[SPR_BYTE_BULLET];
	direction = dir;
	curAnimation = 0;
	curFrame = 0;
	collisionType = CT_BULLET_ENERMY;
	delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 2;
	delayAnimation.maxFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 3;
	vy = 0;
	ay = 0;
	x = xByte;
	y = yByte + 22;
}


Byte_bullet::~Byte_bullet()
{
}
