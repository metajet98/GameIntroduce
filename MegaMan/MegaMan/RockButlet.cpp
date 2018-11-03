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
	int trucQuay = xInViewport - ROCKMAN->width / 2;

	if (direction == sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		mt._41 = 2 * trucQuay;
		mt._11 = -1;
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}

	sprite->draw(xInViewport, yInViewport, 0, 0);

	if (direction == sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}
}


void RockButlet::update()
{		
	vx = direction * 130;
	dx = vx * TIME;
}

void RockButlet::onCollision(BaseObject * S, int nx, int ny)
{
	if (S->collisionType == CT_ENERMY)
	{
		dx = 0;
		dy = 0;
		allowDelete = true;
	}
}

RockButlet::RockButlet()
{
	categoryBullet = OF_MEGAMAN;
	allowDelete = false;
	collisionType = CT_BUTLET;
	sprite = SPRITEMANAGER->sprites[SPR_BUTLET];
	this->width = sprite->animates[0].frames[0].width;
	this->height = sprite->animates[0].frames[0].height;
	curAnimation = 0;
	curFrame = 0;
	direction = ROCKMAN->direction;
	x = ROCKMAN->x + ROCKMAN->width;
	y = ROCKMAN->y + 11;
	if (ROCKMAN->curAnimation == PUSHING_SHOT)
	{
		direction = ROCKMAN->direction == Right ? Left : Right;
		x = ROCKMAN->x+ROCKMAN->width;
		y = ROCKMAN->y + 15;
		
	}
	if (ROCKMAN->curAnimation == RUN_SHOT )
	{
		x = ROCKMAN->x + ROCKMAN->width + direction*(width);
		y = ROCKMAN->y + 10;
	}
}

RockButlet::~RockButlet()
{

}
