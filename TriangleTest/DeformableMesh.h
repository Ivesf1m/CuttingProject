#pragma once

#include "DeformationNode.h"
#include "mesh.h"

class DeformableMesh : public Mesh
{
public:
	DeformableMesh();
	virtual ~DeformableMesh();

	float getDamping();
	void setDamping(float damping);

	float getError();
	void setError(float error);

	float getIntensity();
	void setIntensity(float intensity);

	float getMass();
	void setMass(float mass);

	float getStep();
	void setStep(float step);

	float getStiffness();
	void setStiffness(float stiffness);

	void applyForce(const vec3& force, int vertexIndex);
	void applyForceToAllPoints();
	void initialize();

private:
	float damping;
	float stiffness;
	float mass;
	float error;
	float step;
	float intensity;
	DeformationNode* nodes;
};

