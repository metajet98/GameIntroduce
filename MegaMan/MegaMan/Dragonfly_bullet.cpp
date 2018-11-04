#include "Dragonfly_bullet.h"

List<Dragonfly_bullet*>* Dragonfly_bullet::dragonfly_bullet = 0;

List<Dragonfly_bullet*>* Dragonfly_bullet::getListDragonfly_bullet()
{
	if (dragonfly_bullet == 0)
		dragonfly_bullet = new List<Dragonfly_bullet*>();
	return dragonfly_bullet;
}

void Dragonfly_bullet::update()
{
	if(delayAnimation.canCreateFrame())
		vx = direction * 80;

	MovableObject::update();
}

void Dragonfly_bullet::draw()
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

void Dragonfly_bullet::onCollision(BaseObject * S, int nx, int ny)
{
	//MovableObject::onCollision(S, nx, ny);
}

void Dragonfly_bullet::onAABBCheck(BaseObject * other)
{
	if (other == ROCKMAN && !ROCKMAN->onHit && !ROCKMAN->invisible)
	{
		ROCKMAN->changeAction(ON_HIT);
		ROCKMAN->setOnHit(true);
		this->allowDelete = true;
		ROCKMAN->gameTimeLoop.start();	
	}
}

Dragonfly_bullet::Dragonfly_bullet(int xDragonfly, int yDragonfly, Direction directionDragonfly)
{
	sprite = SPRITEMANAGER->sprites[SPR_DRAGONFLY_BULLET];
	direction = directionDragonfly;
	curAnimation = 0;
	curFrame = 0;
	width = 18;
	height = 14;
	collisionType = CT_BULLET_ENERMY;
	/*this->x = DRAGONFLY->sprite->animates[DRAGONFLY_SHOT].frames[7].x + DRAGONFLY->sprite->animates[DRAGONFLY_SHOT].frames[7].width - this->width-6;
	this->y = DRAGONFLY->sprite->animates[DRAGONFLY_SHOT].frames[7].y + DRAGONFLY->sprite->animates[DRAGONFLY_SHOT].frames[7].height + 7;*/

	this->x = xDragonfly+ 11;
	this->y = yDragonfly + 34;
	delayAnimation.minFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 2;
	delayAnimation.maxFrameTime = ANIMATE_DELAY_TIME_DEFAULT * 3;
	timeDeath.init(0.2, 10);
	timeDeath.start();
}

Dragonfly_bullet::Dragonfly_bullet()
{
	//sprite = SPRITEMANAGER->sprites[SPR_DRAGONFLY_BULLET];
}


Dragonfly_bullet::~Dragonfly_bullet()
{
}
