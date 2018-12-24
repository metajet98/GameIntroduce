#include "BlashHornet.h"


BlashHornet* BlashHornet::instance = 0;
bool BlashHornet::isDeath = false;
int BlashHornet::lifeBoss = BLASHHORNET_Life;


BlashHornet * BlashHornet::getInstance()
{
	if (instance == 0)
		instance = new BlashHornet();
	return instance;
}
BlashHornet::BlashHornet()
{
	alive = true;
	sprite = SPRITEMANAGER->sprites[SPR_BLASHHORNET];
	direction = Left;
	curAnimation = BLASHHORNET_DANCE;
	curFrame = 0;
	allowDraw = true;
	onHit = false;
	damagedTime.init(0.01, 30);
	damagedTime.start();
	timedie.init(0.2, 20);
	timedie.start();
	timeDeath.init(0.2, 20);
	timeDeath.start();
	timePerAnimation.curLoop = 0;
	damage = 1;
	damaged = false;
	x = 4509;
	y = 295;
	width = 50;
	height = 62;
	ay = 0;
	timeAppear.init(0.2, 10);
	timeAppear.start();
	ptsFly = new POINT[2];
	ptsFly[0].x = 4380;
	ptsFly[0].y = 285;
	ptsFly[1].x = 4587;
	ptsFly[1].y = 330;
	r = sqrt((ptsFly[1].y - ptsFly[0].y)*(ptsFly[1].y - ptsFly[0].y) + (ptsFly[1].x - ptsFly[0].x)*(ptsFly[1].x - ptsFly[0].x));
	phi = atan2((ptsFly[1].y - ptsFly[0].y), (ptsFly[1].x - ptsFly[0].x));
	isATT = false;
	re = new RectF(4380, 285, 215, 155);
	timeShot.curLoop = 0;
}


BlashHornet::~BlashHornet()
{
}

void BlashHornet::draw()
{
	if (!allowDraw && curAnimation != BLASHHORNET_DIE) return;
	/*if (!alive)
	{
		dx = 0;
		dy = 0;
		ay = 0;

		if (timeDeath.canCreateFrame())
		{
			sprite = SPRITEMANAGER->sprites[SPR_BOSS_DIE];
			curAnimation = 0;
			curFrame = (curFrame + 1) % 6;
		}

		if (timeDeath.isTerminated())
			return;

		int xInViewport, yInViewport;
		TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);
		sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
		return;
	}*/
	if (BlashHornet::lifeBoss <= 0)
	{

		if (timeDeath.canCreateFrame())
		{
			dy = 10;
			if (DieEffect::getList()->Count < 1 && isOnGround)
			{

				DieEffect* de = new DieEffect(BOSS_DIE);
				int xcen = this->xCenter();
				int ycen = this->yCenter();
				de->x = x + 5;
				de->y = y + 5;
				if (de->curFrame == de->sprite->animates[0].nFrame - 1) de->allowDelete = true;
			}
			AudioManager::getInstance()->StopSound(AUDIO_BOSSSTAGE);
			AudioManager::getInstance()->LoopSound(AUDIO_BOSS_DIE);
		}

		if (timeDeath.isTerminated())
		{
			this->alive = false;
			DieEffect::getList()->Clear();
			ROCKMAN->onAreaBoss = false;
			HORNET->Clear();
			this->isDeath = true;
			return;
		}

		int xInViewport, yInViewport;
		TileMap::curMap->convertToViewportPos(x, y, xInViewport, yInViewport);
		sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);
		return;
	}
	if (alive)
	{
		int xInViewport, yInViewport;
		int deltaY = height - sprite->animates[curAnimation].frames[curFrame].height;
		int deltaX = width - sprite->animates[curAnimation].frames[curFrame].width;
		TileMap::curMap->convertToViewportPos(x + deltaX, y + deltaY, xInViewport, yInViewport);
		int trucQuay = xInViewport + width / 2;

		if (direction != sprite->image->direction)
		{
			D3DXMATRIX mt;
			D3DXMatrixIdentity(&mt);
			mt._41 = 2 * trucQuay;
			mt._11 = -1;
			GRAPHICS->GetSprite()->SetTransform(&mt);
		}
		BLASHHORNET_WING->draw();
		sprite->draw(xInViewport, yInViewport, curAnimation, curFrame);

		if (direction != sprite->image->direction)
		{
			D3DXMATRIX mt;
			D3DXMatrixIdentity(&mt);
			GRAPHICS->GetSprite()->SetTransform(&mt);
		}
	}
}

void BlashHornet::Move8_L_R()
{
	x += 0.85f;
	y = sin((ptsFly[1].x - x) / (ptsFly[1].x - ptsFly[0].x) * 2 * PI);
	if (-1 <= y && y <= 0)
	{
		y = -y * (ptsFly[1].y - (ptsFly[0].y + (ptsFly[1].y - ptsFly[0].y) / 2)) / 1 + (ptsFly[0].y + (ptsFly[1].y - ptsFly[0].y) / 2);
	}
	else
		if ((0 <= y && y <= 1))
		{
			y = ptsFly[0].y + (ptsFly[1].y - ptsFly[0].y) / 2 - y * (ptsFly[0].y + (ptsFly[1].y - ptsFly[0].y) / 2 - ptsFly[0].y) / 1;
		}
}

void BlashHornet::Move8_R_L()
{
	x -= 0.85f;
	y = sin((x - ptsFly[0].x) / (ptsFly[1].x - ptsFly[0].x) * 2 * PI);
	if (-1 <= y && y <= 0)
	{
		y = -y * (ptsFly[1].y - (ptsFly[0].y + (ptsFly[1].y - ptsFly[0].y) / 2)) / 1 + (ptsFly[0].y + (ptsFly[1].y - ptsFly[0].y) / 2);
	}
	else
		if ((0 <= y && y <= 1))
		{
			y = ptsFly[0].y + (ptsFly[1].y - ptsFly[0].y) / 2 - y * (ptsFly[0].y + (ptsFly[1].y - ptsFly[0].y) / 2 - ptsFly[0].y) / 1;
		}
}

void BlashHornet::spawnChild()
{
	changeAction(BLASHHORNET_SHOT);
	if (HORNET->Count < 5) //5 neu la >50%
	{
		if (direction == Left)
		{
			Hornet* hn1 = new Hornet(this->x, this->y, Left, direction * 30, 0, 1);
			Hornet* hn2 = new Hornet(this->x, this->y, Left, direction * 30, 5, 1);
			Hornet* hn3 = new Hornet(this->x, this->y, Left, direction * 30, 10, 1);
			Hornet* hn4 = new Hornet(this->x, this->y, Left, direction * 30, 15, 1);
			Hornet* hn5 = new Hornet(this->x, this->y, Left, direction * 30, 20, 1);
		}
		else
		{
			Hornet* hn1 = new Hornet(this->x + this->width, this->y, Right, direction * 30, 0, 1);
			Hornet* hn2 = new Hornet(this->x + this->width, this->y, Right, direction * 30, 5, 1);
			Hornet* hn3 = new Hornet(this->x + this->width, this->y, Right, direction * 30, 10, 1);
			Hornet* hn4 = new Hornet(this->x + this->width, this->y, Right, direction * 30, 15, 1);
			Hornet* hn5 = new Hornet(this->x + this->width, this->y, Right, direction * 30, 20, 1);
		}
	}
}

void BlashHornet::spawnChildAndFollow()
{
	changeAction(BLASHHORNET_SHOT);
	if (BLASHHORNET_POINT->Count < 1) //5 neu la >50%
	{
		if (direction == Left)
		{
			//Hornet* hn1 = new Hornet(this->x, this->y, Left, direction * 30, 0, 2);
			BlashHornet_Point* bhp = new BlashHornet_Point(this->x, this->y, this->direction);
		}
		else
		{
			//Hornet* hn1 = new Hornet(this->x + this->width, this->y, Right, direction * 30, 0, 2);
			BlashHornet_Point* bhp = new BlashHornet_Point(this->x + this->width, this->y, this->direction);
		}
	}
	if (HORNET->Count < 1) //5 neu la >50%
	{
		if (direction == Left)
		{
			Hornet* hn1 = new Hornet(this->x, this->y, Left, direction * 30, 0, 2);

		}
		else
		{
			Hornet* hn1 = new Hornet(this->x + this->width, this->y, Right, direction * 30, 0, 2);
			
		}
	}
}

void BlashHornet::update()
{
	if (!ROCKMAN->onAreaBoss) return;
	if (ROCKMAN->onAreaBoss && alive)
	{
		AudioManager::getInstance()->StopSound(AUDIO_FIRSTSTAGE);
		AudioManager::getInstance()->Play(AUDIO_BOSSSTAGE);
	}
	if (BlashHornet::lifeBoss <= 0)
	{
		dx = 0;
		changeAction(BLASHHORNET_DIE);
		return;
	}
	if (damaged && alive)
	{
		if (damagedTime.canCreateFrame())
			allowDraw = !allowDraw;
		if (damagedTime.isTerminated())
		{
			damaged = false;
			allowDraw = true;
			damagedTime.start();
		}
		return;
	}

	if (!alive && !BlashHornet::isDeath)
	{
		timedie.canCreateFrame();

		//sound
		//co the them wingame scene vao day
		if (timedie.isTerminated())
			BlashHornet::isDeath = true;
	}

	//mech here
	if (curFrame == sprite->animates[curAnimation].nFrame - 1 && !canUpdate)
	{
		timePerAnimation.curLoop++;
		if (timePerAnimation.curLoop >= 30)
		{
			canUpdate = true;
			timePerAnimation.curLoop = 0;
		}
	}
	if (!canUpdate)
	{
		updateMove();
		ROCKMAN->dx = 0;
		ROCKMAN->dy = 1;
		return;
	}
	if (BlashHornet::lifeBoss >= BLASHHORNET_Life * (2.0f / 3))
	{
		//mech1
		typeATT = 1;
	}
	//else if (BlashHornet::lifeBoss >= BLASHHORNET_Life / 3)
	//{
	//	//mech2
	//	typeATT = 1;
	//}
	else if (BlashHornet::lifeBoss >= BLASHHORNET_Life / 3)
	{
		//mech3

		typeATT = 3;
	}
	
	/*x += direction*(sqrt(2)*cosf(time)) / (sinf(time)*sinf(time) + 1);
	int d = (3 * sqrt(2)*cosf(time)*sinf(time)) / (sinf(time)*sinf(time) + 1);
	y += (3*sqrt(2)*cosf(time)*sinf(time)) / (sinf(time)*sinf(time) + 1);
	time += 0.5f;*/

	//x -= cosf(time);
	//y += sinf(2 * time ) / 2;
	//time += 0.5f;
	/*if(direction==Left) Move8_R_L();
	else Move8_L_R();

	if (x <= ptsFly[0].x)
	{
		direction = Right;
	}
	if (right() >= ptsFly[1].x)
	{
		direction = Left;

	}*/

	updateChangeAnimation();

	if (curAnimation == BLASHHORNET_FLY)
	{
		if (y <= re->top())
		{
			vy = 0;
			vx = 0;
			changeAction(BLASHHORNET_DANCE);
		}
		if (bottom() >= re->bottom())
		{
			vy = -BLASHHORNET_VY;
		}
		if (x <= re->left() || right() >= re->right())
		{
			if (x <= re->left()) direction = Right;
			if (right() >= re->right()) direction = Left;
			vx = 0;
			vy = -BLASHHORNET_VY;
		}
	}

	
	updateMove();
}


void BlashHornet::onCollision(BaseObject * other, int nx, int ny)
{
	if (other->collisionType == CT_GROUND || other->collisionType == CT_DOOR || other->collisionType == CT_DOOR_CAN_MOVE)
	{
		MovableObject::onCollision(other, nx, ny);

		if ((ny == -1 || nx != 0) && curAnimation != BLASHHORNET_DIE)
		{
			changeAction(BLASHHORNET_FLY);
			vy = -BLASHHORNET_VY;
		}
		/*if (nx != 0) direction = (Direction)nx;*/
	}
	if ((ny == -1 || nx != 0) && other->collisionType == CT_PLAYER && curAnimation!=BLASHHORNET_DIE)
	{
		changeAction(BLASHHORNET_FLY);
		vy = -BLASHHORNET_VY;
	}
}

void BlashHornet::onAABBCheck(BaseObject * other)
{
	if (other == ROCKMAN)
	{
		if (!ROCKMAN->onHit && !ROCKMAN->invisible)
		{
			ROCKMAN->changeAction(ON_HIT);
			ROCKMAN->setOnHit(true);
			ROCKMAN->life -= damage;
			ROCKMAN->gameTimeLoop.start();
		}
	}
	if (other->collisionType == CT_BUTLET)
	{
		RockButlet* r = (RockButlet*)other;
		if (!damaged)
		{
			damaged = true;
			if (r->categoryBullet == OF_STRONG_MEGAMAN)
				this->lifeBoss -= 2;
			else if (r->categoryBullet == OF_STRONG_2_MEGAMAN)
			{
				this->lifeBoss -= 3;
			}
			else this->lifeBoss--;
			other->allowDelete = true;
			//gameTimeLoop.start();
		}

		if (lifeBoss <= 0)
		{
			changeAction(BLASHHORNET_DIE);
			vx = 0;
			vy = 100;
			ay = GRAVITY;
			//ROCKMAN->onAreaBoss = false;
		}
	}
}

void BlashHornet::restore(BaseObject * obj)
{
	// nho reset timeDeath
	Enermy::restore(obj);
	alive = true;
	timedie.start();
	BlashHornet::lifeBoss = BLASHHORNET_Life;
	curAnimation = BLASHHORNET_DANCE;
	curFrame = 0;
	allowDraw = true;
	onHit = false;
	damaged = false;
	timePerAnimation.curLoop = 0;
	timeShot.curLoop = 0;
	x = 4509;
	y = 295;
	damagedTime.start();
	canUpdate = false;
	AudioManager::getInstance()->StopSound(AUDIO_BOSSSTAGE);
}

void BlashHornet::updateDirecion()
{
	if (x >= ROCKMAN->x)
		direction = Left;
	else
		direction = Right;
}

void BlashHornet::updateChangeAnimation()
{
	if (curFrame == sprite->animates[curAnimation].nFrame - 1)
	{
		if (curAnimation == BLASHHORNET_DANCE)
		{
			if (typeATT == 1)
			{
				spawnChild();
			}
			else if (typeATT == 3)
			{
				spawnChildAndFollow();
			}
		}
		else if (curAnimation == BLASHHORNET_ATT)
		{
			updateDirecion();
			if (!isATT)
			{
				posRockX = ROCKMAN->x;
				posRockY = ROCKMAN->y;
				if (curFrame == sprite->animates[curAnimation].nFrame - 1)
				{
					vx = posRockX - this->x;
					vy = posRockY - this->y;
					if (bottom() == ROCKMAN->y)
					{
						changeAction(BLASHHORNET_FLY);
						vy = -BLASHHORNET_VY;
					}
				}
				isATT = true;
			}
			else
			{
				//spawnChildAndFollow();
				isATT = false;
			}
		}
		else if (curAnimation == BLASHHORNET_SHOT)
		{
			changeAction(BLASHHORNET_ATT);
		}
	}

}

void BlashHornet::updateMove()
{
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
				curFrame = sprite->animates[curAnimation].nFrame - 1;
			}
			else sprite->animates[curAnimation].next(curFrame);
		}
	}
}

void BlashHornet::updateWing()
{
	BLASHHORNET_WING->update();
}

void BlashHornet::changeAction(int newAction)
{
	if (curAnimation != newAction)
	{
		curFrame = 0;
		curAnimation = newAction;
	}
}

void BlashHornet::updateLocation()
{
	x += dx;
	y += dy;

	BLASHHORNET_WING->dx = dx;
	BLASHHORNET_WING->dy = dy;
	BLASHHORNET_WING->x = x - 20;
	BLASHHORNET_WING->y = y - 23;
}
