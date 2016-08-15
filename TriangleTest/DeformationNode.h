#pragma once

#include <vector>
#include "vertex.h"

using std::vector;

class DeformationNode
{

public:
	DeformationNode();
	~DeformationNode();

	const vector<unsigned int>& getNeighbours();

	const vec3& getAcceleration();
	void setAcceleration(const vec3& accel);

	const vec3& getVelocity();
	void setVelocity(const vec3& vel);

	const vec3& getPoint();
	void setPoint(const vec3& point);

	Vertex* getVertex();

	void update(const vec3& force, float mass, float step, float stiffness);

private:
	Vertex* vertex;
	vector<unsigned int> neighbours;
	vec3 acceleration, velocity, point;
};

