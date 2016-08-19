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

	unsigned int getNumberOfPoints();

private:
	vector<vec3> collisionPoints;
};

