#include "CollisionManager.h"


CollisionManager*CollisionManager::instance = 0;

CollisionManager * CollisionManager::getInstance()
{
	if (instance == 0)
		instance = new CollisionManager();
	return instance;
}

RectF CollisionManager::getBroadphaseBox(Box & M)
{
	float x, y, w, h;
	x = M.dx > 0 ? M.x : M.x + M.dx;
	y = M.dy > 0 ? M.y : M.y + M.dy;
	w = M.dx > 0 ? M.width + M.dx : M.width - M.dx;
	h = M.dy > 0 ? M.height + M.dy : M.height - M.dy;

	RectF broadphasebox(x, y, w, h);
	return broadphasebox;
}

bool CollisionManager::AABBCheck(RectF & M, RectF & S)
{
	return (M.bottom() > S.top() && M.top() < S.bottom() && M.left() < S.right() && M.right() > S.left());
}

float CollisionManager::sweptAABB(Box * M, RectF * S, int & normalX, int & normalY)
{
	normalX = 0;
	normalY = 0;

	float dxEntry, dyEntry;
	float dxExit, dyExit;

	if (M->dx > 0.0f)
	{
		dxEntry = S->x - (M->x + M->width);
		dxExit = (S->x + S->width) - M->x;
	}
	else
	{
		dxEntry = (S->x + S->width) - M->x;
		dxExit = S->x - (M->x + M->width);
	}

	if (M->dy > 0.0f)
	{
		dyEntry = S->y - (M->y + M->height);
		dyExit = (S->y + S->height) - M->y;
	}
	else
	{
		dyEntry = (S->y + S->height) - M->y;
		dyExit = S->y - (M->y + M->height);
	}

	float txEntry, tyEntry;
	float txExit, tyExit;

	if (M->dx == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / M->dx;
		txExit = dxExit / M->dx;
	}

	if (M->dy == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / M->dy;
		tyExit = dyExit / M->dy;
	}

	float entryTime = max(txEntry, tyEntry);
	float exitTime = min(txExit, tyExit);

	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f)
	{
		return 1.0f;
	}
	else
	{
		if (txEntry > tyEntry)
		{
			if (M->dx < 0.0f)
			{
				normalX = 1.0f;
				normalY = 0.0f;
			}
			else
			{
				normalX = -1.0f;
				normalY = 0.0f;
			}
		}
		else
		{
			if (M->dy < 0.0f)
			{
				normalX = 0.0f;
				normalY = 1.0f;
			}
			else
			{
				normalX = 0.0f;
				normalY = -1.0f;
			}
		}
		return entryTime;
	}
}

void CollisionManager::checkCollision(BaseObject * M, BaseObject * S)
{
	if (!M->alive && !S->alive)
		return;
	M->dx -= S->dx;
	M->dy -= S->dy;

	RectF broadPhase = getBroadphaseBox(*M);
	if (AABBCheck(broadPhase, *S))
	{
		if (AABBCheck(*M, *S))
		{
			M->onAABBCheck(S);
			S->onAABBCheck(M);

			M->dx += S->dx;
			M->dy += S->dy;

			return;
		}
		int nx, ny;
		float sweptTime = sweptAABB(M, S, nx, ny);
		if (sweptTime < 1.0f)
		{
			M->onCollision(S, nx, ny);
			S->onCollision(M, nx, ny);
		}
		remainingtime = 1.0f - sweptTime;
	}
	M->dx += S->dx;
	M->dy += S->dy;
}

void CollisionManager::preventMove(BaseObject * M, BaseObject * S)
{
	if (M->top() < S->bottom() && M->bottom() > S->top() && M->dx != 0)
	{
		M->isCollision = true;
		if (M->dx > 0)
			M->dx = S->left() - M->right() - 0.1f;
		else
			M->dx = S->right() - M->left() + 0.1f;
		return;
	}

	if (M->left() < S->right() && M->right() > S->left() && M->dy != 0)
	{
		M->isCollision = true;
		if (M->dy > 0)
			M->dy = S->top() - M->bottom() - 0.1f;
		else
			M->dy = S->bottom() - M->top() + 0.1f;
		return;
	}

	M->isCollisionCross = true;
}

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}
