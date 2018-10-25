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
	x += direction * 10;
}

void RockButlet::onCollision(BaseObject * S, int nx, int ny)
{
	/*MovableObject::onCollision(S, nx, ny);
	if (nx == -1 || nx == 1) getListBullet()->_Remove(this);*/
}

RockButlet::RockButlet()
{
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
