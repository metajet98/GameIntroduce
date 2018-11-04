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
	if (S->collisionType == CT_GROUND)
	{
		if ((curAnimation == JUMP || curAnimation == PUSHING || curAnimation == PUSHING_SHOT || curAnimation==HIGH_JUMP) && (nx == -1 || nx == 1))
			onCollisionPush(S, nx, ny);
		MovableObject::onCollision(S, nx, ny);
		if (ny == 1) vy = 0;
	}

	if (onHit && isOnGround)
	{
		invisible = true;
		setOnHit(false);
		vx = 0;
	}

}

void Rockman::updateLocation()
{
	if (!alive)
		return;

	/*if (isCollisionCross && !isCollision)
	{
		if (abs(dx) > abs(dy))
			dy = 0;
		else
			dx = 0;
	}*/
	x += dx;
	y += dy;
}



void Rockman::draw()
{	
	if (sprite == 0) return;

	if (!allowDraw)
		return;

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
		 if (ROCKBUTLET->Count < 1)
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

void Rockman::setOnHit(bool newOnHit)
{
	if (newOnHit)
	{
		changeAction(ON_HIT);
		vx = -50 * direction;
		vy = -80;
	}

	onHit = newOnHit;
}

void Rockman::updateInvisible()
{
	if (invisible)
	{
		if (gameTimeLoop.canCreateFrame())
			allowDraw = !allowDraw;

		if (gameTimeLoop.isTerminated())
		{
			allowDraw = true;
			setOnHit(false);
			invisible = false;
		}
	}
}

void Rockman::die()
{
	if (!alive)
	{
		if (DieEffect::getList()->Count < 8)
		{
			DieEffect* effect1 = new DieEffect(ROCK_DIE);
			effect1->x = this->x;
			effect1->y = this->y;
			effect1->dx = -1;
			effect1->dy = -1;

			DieEffect* effect2 = new DieEffect(ROCK_DIE);
			effect2->x = this->x + width / 2;
			effect2->y = this->y;
			effect2->dx = 0;
			effect2->dy = -1;

			DieEffect* effect3 = new DieEffect(ROCK_DIE);
			effect3->x = this->x + width;
			effect3->y = this->y;
			effect3->dx = 1;
			effect3->dy = -1;

			DieEffect* effect4 = new DieEffect(ROCK_DIE);
			effect4->x = this->x;
			effect4->y = this->y + height / 2;
			effect4->dx = -1;
			effect4->dy = 0;

			DieEffect* effect5 = new DieEffect(ROCK_DIE);
			effect5->x = this->x;
			effect5->y = this->y + height;
			effect5->dx = -1;
			effect5->dy = 1;

			DieEffect* effect6 = new DieEffect(ROCK_DIE);
			effect6->x = this->x + width / 2;
			effect6->y = this->y + height;
			effect6->dx = 0;
			effect6->dy = 1;

			DieEffect* effect7 = new DieEffect(ROCK_DIE);
			effect7->x = this->x + width;
			effect7->y = this->y + height;
			effect7->dx = 1;
			effect7->dy = 1;

			DieEffect* effect8 = new DieEffect(ROCK_DIE);
			effect8->x = this->x + width;
			effect8->y = this->y + height / 2;
			effect8->dx = 1;
			effect8->dy = 0;
		}
		dx = 0;
		dy = 0;
	}
}

void Rockman::update()
{
	if (onHit)
	{
		MovableObject::update();
		return;
	}
	updateInvisible();
	if (life <= 0)
	{
		alive = false;
		changeAction(DIE);
		die();
		return;
	}

	//if (!updatePause()) return;

	updateDirection();
	updateChangeAnimation();
	MovableObject::update();
}

void Rockman::updateDirection()
{
	if (KEY->keyLeft && (curAnimation!=ON_HIT ))
		direction = Left;
	if (KEY->keyRight && curAnimation != ON_HIT)
	{
		direction = Right;
	}
	if (KEY->keyMove && ((curAnimation != JUMP_SHOT && curAnimation != SHOT && curAnimation != PUSHING_JUMP) || !isOnGround))
	{
		vx = ROCKMAN_VX_GO * direction;
		if (curAnimation == APPEAR || curAnimation == ON_HIT) vx = 0;
		if (curAnimation == HIGH_JUMP) vx *= 2;

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
			if (KEY->keyJumpPress && curAnimation!=SLIDING)
			{
				vy = -170;
				//curFrame = 0;
				
				//isOnGround = false;
			}
			else
			{
				if (KEYBOARD->IskeyUp(DIK_X)) isSliding = true;

				if (KEY->keySlide && isSliding)
				{
					changeAction(SLIDING);
					vx = direction * ROCKMAN_VX_GO * 3;
					if (curFrame == sprite->animates[SLIDING].nFrame - 1) isSliding = false;
					
					if (KEY->keyJumpPress && isSliding)
					{
						
						changeAction(HIGH_JUMP);
						vy = -210;
						vx = direction * ROCKMAN_VX_GO * 3;
					}
					
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
					if (curAnimation == APPEAR) return;
					//co the doi animation hight jump o day
					if (curAnimation != ON_HIT );
					{
						changeAction(JUMP); 
					}
				}
				
				isPushing = false;
			}
		}
	
}
Rockman::Rockman()
{
	sprite = SPRITEMANAGER->sprites[SPR_MAIN];
	//x = 126;
	//y = 680;
	x = 680;
	y = 132;
	direction = Right;
	width = 25;
	height = 26;
	inAir = false;
	isPushing = false;
	pauseAnimation = false;
	isSliding = true;
	curAnimation = 0;
	collisionType = CT_PLAYER;
	gameTimeLoop.init(0.01, 30);
	gameTimeLoop.start();
	life = 23;
	alive = true;
	invisible = false;
	allowDraw = true;
}


Rockman::~Rockman()
{
}
