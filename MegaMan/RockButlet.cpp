#include "RockButlet.h"

List<RockButlet*>* RockButlet::bullets = 0;


List<RockButlet*>* RockButlet::getListBullet()
{
	if (bullets == 0)
		bullets = new List<RockButlet*>();
	return bullets;
}

void RockButlet::draw()
{
	int xInViewport, yInViewport;
	TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);
	int trucQuay = (xInViewport +ROCKMAN->width);
	/*if (ROCKMAN->curAnimation == PUSHING && this->categoryBullet != OF_MEGAMAN)
		direction = ROCKMAN->direction == Right ? Left : Right;*/
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


void RockButlet::update()
{		
	
	vx = direction * 120;
	isOnGround = false;
	updateVerlocity();
	if (!alive) return;

	BaseObject::update();
	if (!pauseAnimation)
	{
		if (delayAnimation.canCreateFrame())
		{
			if (curFrame == sprite->animates[curAnimation].nFrame - 1)
			{
				curFrame = 0;
			}
			else sprite->animates[curAnimation].next(curFrame);
		}
	}
}

void RockButlet::onCollision(BaseObject * S, int nx, int ny)
{
	
}

void RockButlet::onAABBCheck(BaseObject * other)
{
	if (this->categoryBullet != OF_STRONG_2_MEGAMAN)
		this->allowDelete = true;
}

void RockButlet::changeDirection(Direction dir)
{
}

RockButlet::RockButlet(CATEGORY_BULLET_FOR_MEGAMAN level)
{
	categoryBullet = level;
	allowDelete = false;
	collisionType = CT_BUTLET;
	sprite = SPRITEMANAGER->sprites[SPR_BUTLET];
	curAnimation = level;
	curFrame = 0;
	ay = 0;
	if (level == OF_MEGAMAN)
	{
		x = ROCKMAN->x + ((direction == Right) ? -1 : -2)*8;
		y = ROCKMAN->yCenter() - height / 2 -2;
		direction = ROCKMAN->direction;
		if (ROCKMAN->curAnimation == PUSHING_SHOT)
		{
			direction = ROCKMAN->direction == Right ? Left : Right;
			x = ROCKMAN->x + ((direction == Right) ? -1 : -2) * 8;
			y = ROCKMAN->yCenter() + height / 2;
		}
	}
	else
	{
		direction = ROCKMAN->direction;
		x = ROCKMAN->x + ((direction == Right) ? 0 : -1) * (ROCKMAN->width - 8);
		y = ROCKMAN->yCenter() - height / 2-9;
		if (ROCKMAN->isPushing)
		{
			direction = ROCKMAN->direction == Right ? Left : Right;
			x = ROCKMAN->x + ((direction == Right) ? 1 : -2) * (ROCKMAN->width - 8);
			y = ROCKMAN->yCenter() - height / 3-9;
		}
	}
	if (categoryBullet == OF_MEGAMAN)
	{
		width = height = 8;
	}
	else if (categoryBullet == OF_STRONG_MEGAMAN)
	{
		width = 38;
		height = 21;
	}
	else if (categoryBullet == OF_STRONG_2_MEGAMAN)
	{
		width = 46;
		height = 31;
	}
}

RockButlet::RockButlet(CATEGORY_BULLET_FOR_MEGAMAN level, Direction dir)
{
	
}

RockButlet::~RockButlet()
{

}
