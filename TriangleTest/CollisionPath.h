#pragma once

#include <vector>
#include "glm.hpp"

using std::vector;
using glm::vec3;

class CollisionPath
{
public:
	CollisionPath();
	~CollisionPath();

	void addPoint(vec3& point);
	void removePoint(unsigned int index);
	void removeAllPoints();

	vector<vec3>& getCollisionPoints();

	void addIndex(unsigned int index);
	void removeIndex(unsigned int index);
	void removeAllIndices();

	vector<unsigned int>& getCollisionIndices();

	unsigned int getNumberOfPoints();

private:
	vector<vec3> collisionPoints;
	vector<unsigned int> collisionIndices;
};

