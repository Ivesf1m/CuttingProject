#include "DeformationNode.h"



DeformationNode::DeformationNode()
	: vertex(NULL)
{
}


DeformationNode::~DeformationNode()
{
}

vector<unsigned int>& DeformationNode::getNeighbours()
{
	return neighbours;
}

const vec3& DeformationNode::getAcceleration()
{
	return acceleration;
}

void DeformationNode::setAcceleration(const vec3& accel)
{
	this->acceleration = accel;
}

const vec3& DeformationNode::getVelocity()
{
	return velocity;
}

void DeformationNode::setVelocity(const vec3& vel)
{
	this->velocity = vel;
}

const vec3& DeformationNode::getPoint()
{
	return point;
}

void DeformationNode::setPoint(const vec3& point)
{
	this->point = point;
}

Vertex * DeformationNode::getVertex()
{
	return vertex;
}

void DeformationNode::setVertex(Vertex* v)
{
	this->vertex = v;
	//NEED TO CHECK THIS!!!!
	this->point = v->position();
}

void DeformationNode::update(const vec3& force, float mass, float step, float stiffness)
{
	acceleration = (force - stiffness * velocity) / mass;
	velocity = acceleration * step;
}
