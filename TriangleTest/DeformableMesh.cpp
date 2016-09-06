#include "DeformableMesh.h"
#include <algorithm>

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

void DeformableMesh::applyForceToAllPoints()
{
	vec3 shift, force, f;

	for (unsigned int i = 0; i < this->numberOfVertices; ++i) {
		float vdotv = glm::dot(nodes[i].getVelocity(), nodes[i].getVelocity());
		float adota = glm::dot(nodes[i].getAcceleration(), nodes[i].getAcceleration());
		if (vdotv > error || adota > error) {
			force = nodes[i].getVertex()->position();
			force = damping * (nodes[i].getPoint() - force);
			nodes[i].update(force, mass, step, stiffness);
			shift = step * nodes[i].getVelocity();
			vec3 pos = nodes[i].getVertex()->position() + shift;
			nodes[i].getVertex()->setPosition(pos);
		}
		else {
			nodes[i].getVertex()->setPosition(nodes[i].getPoint());
		}
	}
}

void DeformableMesh::initialize()
{
	if (numberOfVertices == 0)
		return;

	nodes = new DeformationNode[numberOfVertices];
	for (unsigned int i = 0; i < numberOfVertices; ++i) {
		nodes[i].setVertex(&vertices[i]);
		vector<unsigned int>& neighbors = nodes[i].getNeighbours();
		for (unsigned int j = 0; j < numberOfIndices; j += 3) {			
			if (indices[j] == i) {
				neighbors.push_back(indices[j + 1]);
				neighbors.push_back(indices[j + 2]);
			}else if (indices[j + 1] == i) {
				neighbors.push_back(indices[j]);
				neighbors.push_back(indices[j + 2]);
			}else if (indices[j + 2] == i) {
				neighbors.push_back(indices[j]);
				neighbors.push_back(indices[j + 1]);
			}
		}

		//Removing possible duplicates
		std::sort(neighbors.begin(), neighbors.end());
		vector<unsigned int>::iterator it;
		it = std::unique(neighbors.begin(), neighbors.end());
		neighbors.erase(it, neighbors.end());
	}
}
