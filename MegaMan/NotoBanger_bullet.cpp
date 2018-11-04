#include "NotoBanger_bullet.h"

List<NotoBanger_bullet*>* NotoBanger_bullet::notobanger_bullet = 0;

List<NotoBanger_bullet*>* NotoBanger_bullet::getListnotobanger_bullet()
{
	if (notobanger_bullet == 0)
		notobanger_bullet = new List<NotoBanger_bullet*>();
	return notobanger_bullet;
}

void NotoBanger_bullet::update()
{
	timeShot.canCreateFrame();
	vx = 50 * direction;
	dx = vx * TIME;
	if (timeShot.isTerminated())
	{
		MovableObject::update();
		timeShot.start();
	}
}

void NotoBanger_bullet::draw()
{
	int xInViewport, yInViewport;
	TileMap::curMap->convertToViewportPos(this->x, this->y, xInViewport, yInViewport);
	int trucQuay = xInViewport + width / 2;

	if (direction != sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		mt._41 = 2 * trucQuay;
		mt._11 = -1;
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}

	sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);

	if (direction != sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}
}

void NotoBanger_bullet::onCollision(BaseObject * S, int nx, int ny)
{
}

void NotoBanger_bullet::onAABBCheck(BaseObject * other)
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

NotoBanger_bullet::NotoBanger_bullet(int xNotobanger, int yNotobanger, Direction directionNotobanger)
{
	sprite = SPRITEMANAGER->sprites[SPR_NOTORBANGER_BULLET];
	direction = directionNotobanger;
	curAnimation = 0;
	curFrame = 0;
	width = 8;
	height = 8;
	collisionType = CT_BULLET_ENERMY;
	this->x = xNotobanger-1;
	this->y = yNotobanger + 2;
	delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 2;
	delayAnimation.maxFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 3;
	timeShot.init(0.1,1);
	timeShot.start();
}

NotoBanger_bullet::NotoBanger_bullet()
{
}


NotoBanger_bullet::~NotoBanger_bullet()
{
}
