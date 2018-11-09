#include "Rhino.h"

Rhino* Rhino::instance = 0;
Rhino * Rhino::getInstance()
{
	if (instance == 0)
		instance = new Rhino();
	return instance;
}

void Rhino::updateBlink()
{
	if (isBlink)
	{
		if (BlinkTime.canCreateFrame())
			allowDraw = !allowDraw;
		if (BlinkTime.isTerminated())
		{
			allowDraw = true;
			setOnHit(false);
			isBlink = false;
		}
	}
}

void Rhino::draw()
{
	if (sprite == 0) return;

	if (!alive) return;

	if (!allowDraw)
		return;

	int xInViewport, yInViewport;
	TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);
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

void Rhino::update()
{
	if (!ROCKMAN->onAreaBoss) return;
	//update direction
	if (alive && isOnGround)
	{
		int delta = ROCKMAN->xCenter() - xCenter();
		direction = delta < 0 ? Left : Right;

		if (damagedTime.isTerminated())
		{
			if (curAnimation == RA_IsDAMAGED)
			{
				vx = 0;
				curAnimation = randomAnimation();
				changeAction(curAnimation);
			}

			switch (curAnimation)
			{
			case RA_ATT:
			case RA_MOVE:
				if (delta <= 2 && delta >= -2)
				{
					curAnimation = RA_ATT;
					changeAction(curAnimation);
				}
				else
				{
					vx = delta == 0 ? 0 : 20 * direction;
					if (timePerAnimation.isTerminated())
					{
						timePerAnimation.start();
						curAnimation = randomAnimation();
					}
				}
				break;
			case RA_SHOT:

			default:
				break;
			}
		}
	}
	MovableObject::update();
}

void Rhino::onCollision(BaseObject * other, int nx, int ny)
{
	MovableObject::onCollision(other, nx, ny);
}

void Rhino::onAABBCheck(BaseObject * other)
{
}

void Rhino::setOnHit(bool newOnHit)
{
	if (newOnHit)
	{
		changeAction(ON_HIT);
		vx = -50 * direction;
		vy = -80;
	}

	onHit = newOnHit;
}

void Rhino::updateMach()
{
}

void Rhino::die()
{
}

void Rhino::restore(BaseObject * obj)
{
}
void Rhino::changeAction(int newAction)
{
	if (curAnimation != newAction)
	{
		curFrame = 0;
		curAnimation = newAction;
	}
}
RHINO_ACTION Rhino::randomAnimation()
{
	srand(time(NULL));
	int result = rand() % 100;
	if (result >= 0 && result <= 20)
		return RA_ATT;
	if (result > 20 && result <= 80)
		return RA_MOVE;
	else
		return RA_SHOT;
}
Rhino::Rhino()
{
	alive = true;
	sprite = SPRITEMANAGER->sprites[SPR_RHINO];
	curAnimation = RA_STAND;
	curFrame = 0;
	life = 24;
	BlinkTime.init(0.01, 10);
	BlinkTime.start();
	direction = Left;
	appearHP = false;
	isBlink = false;
	allowDraw = true;
	width = 87;
	height = 45;
	onHit = false;
}


Rhino::~Rhino()
{
}