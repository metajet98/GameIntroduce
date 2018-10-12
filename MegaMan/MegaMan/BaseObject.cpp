#include "BaseObject.h"
#include<stdlib.h>

#ifndef _DEBUG
#pragma pop_macro("realloc")
#pragma pop_macro("malloc")
#pragma pop_macro("free")
#pragma pop_macro("calloc")
#pragma pop_macro("_recalloc")
#pragma pop_macro("_msize")
#pragma pop_macro("_freea")
#pragma pop_macro("_expand")
#pragma pop_macro("_aligned_recalloc")
#pragma pop_macro("_aligned_realloc")
#pragma pop_macro("_aligned_offset_recalloc")
#pragma pop_macro("_aligned_offset_realloc")
#pragma pop_macro("_aligned_offset_malloc")
#pragma pop_macro("_aligned_msize")
#pragma pop_macro("_aligned_malloc")
#pragma pop_macro("_aligned_free")

void* operator new(std::size_t sz)
{
	void* m = ::malloc(sz);
	memset(m, 1, sz);
	return m;
}
#endif

void BaseObject::update()
{
	isCollisionCross = false;
	isCollision = false;
}

void BaseObject::draw()
{
}

void BaseObject::onCollision(BaseObject * other, int nx, int ny)
{
}

void BaseObject::onAABBCheck(BaseObject * other)
{
}

BaseObject::BaseObject()
{
	collisionType = CT_GROUND;
}

void BaseObject::updateLocation()
{


	x += dx;
	y += dy;
}

RectF BaseObject::oldRect()
{
	return RectF(oldX, oldY, width, height);
}

BaseObject::~BaseObject()
{
}
