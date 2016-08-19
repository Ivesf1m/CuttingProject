#include "CollisionPath.h"



CollisionPath::CollisionPath()
{
}


CollisionPath::~CollisionPath()
{
}

void CollisionPath::addPoint(vec3& point)
{
	this->collisionPoints.push_back(point);
}

void CollisionPath::removePoint(unsigned int index)
{
	if (index >= collisionPoints.size())
		return;

	collisionPoints.erase(collisionPoints.begin() + index);
}

void CollisionPath::removeAllPoints()
{
	collisionPoints.clear();
}

unsigned int CollisionPath::getNumberOfPoints()
{
	return static_cast<unsigned int>(collisionPoints.size());
}
