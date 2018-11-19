#include "Rhino_bullet.h"


List<Rhino_bullet*>* Rhino_bullet::rhinobullet = 0;
List<Rhino_bullet*>* Rhino_bullet::getListBossBullet()
{
	if (rhinobullet == 0)
		return rhinobullet = new List<Rhino_bullet*>();
	return rhinobullet;
}

void Rhino_bullet::update()
{
	vx = direction * 100;
	dx = vx * TIME;
	DrawableObject::update();
}

void Rhino_bullet::draw()
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

void Rhino_bullet::onCollision(BaseObject * S, int nx, int ny)
{
}

void Rhino_bullet::onAABBCheck(BaseObject * other)
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

Rhino_bullet::Rhino_bullet(int xRhino, int yRhino, Direction directionRhino)
{
	sprite = SPRITEMANAGER->sprites[SPR_RHINO_BULLET];
	direction = directionRhino;
	curAnimation = 0;
	curFrame = 0;
	collisionType = CT_BULLET_ENERMY;
	x = xRhino;
	y = yRhino + 25;
	width = 35;
	height = 15;
	delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 2;
	delayAnimation.maxFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 3;
	vy = 0;
	ay = 0;
}

Rhino_bullet::Rhino_bullet()
{
}


Rhino_bullet::~Rhino_bullet()
{
}
