#include "DeformableMesh.h"

using glm::dot;

DeformableMesh::DeformableMesh()
	: error(0.0001f), step(0.08f), intensity(1.0f), nodes(NULL)
{
}


DeformableMesh::~DeformableMesh()
{
	delete[] nodes;
}

float DeformableMesh::getDamping()
{
	return damping;
}

void DeformableMesh::setDamping(float damping)
{
	this->damping = damping;
}

float DeformableMesh::getError()
{
	return error;
}

void DeformableMesh::setError(float error)
{
	this->error = error;
}

float DeformableMesh::getIntensity()
{
	return intensity;
}

void DeformableMesh::setIntensity(float intensity)
{
	this->intensity = intensity;
}

float DeformableMesh::getMass()
{
	return mass;
}

void DeformableMesh::setMass(float mass)
{
	this->mass = mass;
}

float DeformableMesh::getStep()
{
	return step;
}

void DeformableMesh::setStep(float step)
{
	this->step = step;
}

float DeformableMesh::getStiffness()
{
	return stiffness;
}

void DeformableMesh::setStiffness(float stiffness)
{
	this->stiffness = stiffness;
}

void DeformableMesh::applyForce(const vec3& force, int vertexIndex)
{
	if (this->numberOfVertices == 0) {
		cerr << "Error: cannot deform mesh with 0 vertices." << endl;
		return;
	}

	vec3 shift, p, f;
	nodes[vertexIndex].update(force, mass, step, stiffness);
	shift = step * nodes[vertexIndex].getVelocity();
	Vertex* vertex = nodes[vertexIndex].getVertex();
	vertex->setPosition(vertex->position() + shift);

	for (unsigned int i = 0; i < nodes[vertexIndex].getNeighbours().size(); ++i) {
		f = damping * shift;
		unsigned int neighbourIndex = nodes[vertexIndex].getNeighbours()[i];
		nodes[neighbourIndex].update(force, mass, step, stiffness);
		shift = step * nodes[neighbourIndex].getVelocity();
		vertex = nodes[neighbourIndex].getVertex();
		vertex->setPosition(vertex->position() + shift);
	}
	
}

void DeformableMesh::applyForceAllPoints()
{
	vec3 shift, p, f;
	//float d;

	for (unsigned int i = 0; i < this->numberOfVertices; ++i) {
		float vdotv = glm::dot(nodes[i].getVelocity(), nodes[i].getVelocity());
		float adota = glm::dot(nodes[i].getAcceleration(), nodes[i].getAcceleration());
		if (vdotv > error || adota > error) {
			//Terminar
		}
	}
}
