#pragma once

#include "mesh.h"
#include "ray.h"

class CollisionDetector
{
public:
	CollisionDetector(Mesh* mesh, Ray* ray);
	~CollisionDetector();

	//Getters and setters.
	Mesh* getMesh();
	void setMesh(Mesh* mesh);

	Ray* getRay();
	void setRay(Ray* ray);

	void testCollision();

private:
	Mesh* mesh;
	Ray* ray;
	vec3 collisionPoint;
	bool collided;

	//Implementation of the collision test developed by Akenine and Moller
	//for triangles and rays.
	bool akenineMollerCollisionTest(unsigned int index);
};

