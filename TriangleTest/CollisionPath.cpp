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

void CollisionPath::addIndex(unsigned int index)
{
	collisionIndices.push_back(index);
}

void CollisionPath::removeIndex(unsigned int index)
{
	if (index >= collisionIndices.size())
		return;
	collisionIndices.erase(collisionIndices.begin() + index);
}

void CollisionPath::removeAllIndices()
{
	collisionIndices.clear();
}

vector<vec3>& CollisionPath::getCollisionPoints()
{
	return collisionPoints;
}

vector<unsigned int>& CollisionPath::getCollisionIndices()
{
	return collisionIndices;
}
