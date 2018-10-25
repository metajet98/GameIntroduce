#include "Rockman.h"


Rockman* Rockman::instance = 0;
Rockman * Rockman::getInstance()
{

	if (instance == 0)
		instance = new Rockman();
	return instance;
}
void Rockman::onCollisionPush(BaseObject*S, int nx, int ny)
{
	float magnitude = sqrt(vx*vx + vy * vy) * COLLISION->remainingtime;
	float dotprod = vx * nx + vy * ny;
	if (dotprod > 0.0f)
	{
		dotprod = 1.0f;
	}
	else
	{
		dotprod = -1.0f;
	}
	vx = dotprod * nx*magnitude;
	vy = dotprod * ny*magnitude;	
	isPushing = true;
}
void Rockman::onCollision(BaseObject*S, int nx, int ny)
{
	if((curAnimation==JUMP || curAnimation==PUSHING || curAnimation==PUSHING_SHOT)&&(nx==-1||nx==1))
		onCollisionPush(S, nx, ny);
	MovableObject::onCollision(S,nx,ny);
	if (ny == 1) vy = 0;
	if (nx == -1 || nx == 1) vx = 0;

	if (onHit)
	{
		//curAnimation = ON_HIT;
		setOnHit(false);
		//vx = 0;
	}

}

void Rockman::updateLocation()
{
	x += dx;
	y += dy;
}



void Rockman::draw()
{	
	if (sprite == 0) return;
	int xInViewport, yInViewport;
	TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);
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

	 if ((curAnimation == SHOT) || (curAnimation == JUMP_SHOT) || ((curAnimation == PUSHING_SHOT) && isPushing) || (curAnimation == RUN_SHOT))
	 {
		 if (ROCKBUTLET->Count < 4)
		 {
			 RockButlet *butlet = new RockButlet();
			 RockButlet::getListBullet()->_Add(butlet);
		 }
	 }

	if (direction == sprite->image->direction)
	{
		D3DXMATRIX mt;
		D3DXMatrixIdentity(&mt);
		GRAPHICS->GetSprite()->SetTransform(&mt);
	}
}

void Rockman::changeAction(int newAction)
{
	if(curAnimation!=newAction)
		curAnimation = newAction;
	
	DrawableObject::changeAction(newAction);
}

bool Rockman::setOnHit(bool newOnHit)
{
	if (newOnHit)
	{
		//changeAction(ON_HIT);
		vx = -5 * direction;
		vy = -100;
	}

	onHit = newOnHit;
	return onHit;
}

void Rockman::update()
{
	updateDirection();
	updateChangeAnimation();
	MovableObject::update();
}

void Rockman::updateDirection()
{
	if (KEY->keyLeft)
		direction = Left;
	if (KEY->keyRight)
	{
		direction = Right;
	}
	if (KEY->keyMove && ((curAnimation!=JUMP_SHOT &&  curAnimation!=SHOT && curAnimation!= PUSHING_JUMP) || !isOnGround))
	{
		vx = ROCKMAN_VX_GO * direction;
	}
	else
	{
		vx = 0;
	}
}

void Rockman::updateChangeAnimation()
{
	if (isOnGround)
		{
			if (KEY->keyJumpPress)
			{
				vy = -170;
				//curFrame = 0;
				isOnGround = false;
			}
			else
			{
				if (KEYBOARD->IskeyUp(DIK_X)) isSliding = true;

				if (KEY->keySlide && isSliding)
				{
					changeAction(SLIDING);
					vx = direction * ROCKMAN_VX_GO * 3;
					if (curFrame == sprite->animates[SLIDING].nFrame - 1) isSliding = false;
				}

				else

					if (KEY->keyMove)
					{

						changeAction(MOVE);

						if (KEY->keyAttack)
						{
							changeAction(RUN_SHOT);
						}
					}
					else
					{
						changeAction(STAND);
						if (KEY->keyAttack)
						{
							changeAction(SHOT);
						}
					}
				isPushing = false;
			}
		}
	else
		{

			if (KEY->keyAttack && !isPushing && curAnimation != ON_HIT)
			{
				changeAction(JUMP_SHOT);
			}
			else
			{
				if (isPushing && curAnimation != ON_HIT)
				{
					curFrame = 0;
					changeAction(PUSHING);

					if (KEY->keyJumpPress && KEY->keyMove)
					{
						changeAction(PUSHING_JUMP);
						vx = direction * ROCKMAN_VX_GO - 50;
						vy = -170;
					}





					if (KEY->keyAttack)
						changeAction(PUSHING_SHOT);
				}
				else
				{
					
					if (curAnimation != ON_HIT && curAnimation != APPEAR)
						changeAction(JUMP);
				}
				
				isPushing = false;
			}
		}
	
}
Rockman::Rockman()
{
	sprite = SPRITEMANAGER->sprites[SPR_MAIN];
	x = 126;
	y = 680;
	direction = Right;
	width = 25;
	height = 26;
	inAir = false;
	isPushing = false;
	pauseAnimation = false;
	isSliding = true;
	curAnimation = 0;
	collisionType = CT_PLAYER;
}


Rockman::~Rockman()
{
}
