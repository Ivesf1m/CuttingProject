#include "CollisionDetector.h"

#define EPSILON 1e-5
#define LAMBDA_TOLERANCE 0.3f

CollisionDetector::CollisionDetector(Mesh* mesh, Ray* ray)
	: mesh(mesh), ray(ray), collided(false)
{
}


CollisionDetector::~CollisionDetector()
{
}

Mesh* CollisionDetector::getMesh()
{
	return mesh;
}

void CollisionDetector::setMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

Ray* CollisionDetector::getRay()
{
	return ray;
}

void CollisionDetector::setRay(Ray* ray)
{
	this->ray = ray;
}

/* This is the non-culling version*/
bool CollisionDetector::akenineMollerCollisionTest(unsigned int index)
{
	vec3 edge1, edge2;
	vec3 p, q, t;
	//u and v are the barycentric coordinates of the point of
	//intersection in the triangle (should it exist)
	float det, inv_det, u, v;
	float lambda;

	//Calculating edges
	vec3 v1 = mesh->getVertex(mesh->getIndex(index)).position();
	vec3 v2 = mesh->getVertex(mesh->getIndex(index + 1)).position();
	vec3 v3 = mesh->getVertex(mesh->getIndex(index + 2)).position();

	edge1 = v2 - v1;
	edge2 = v3 - v1;

	//Calculating determinant
	p = glm::cross(ray->getDirection(), edge2);
	det = glm::dot(edge1, p);

	//If the determinant is close to 0, the ray must be in the triangle's plane.
	if (det > -EPSILON && det < EPSILON)
		return false;

	inv_det = 1.0f / det;

	//Vector from v1 to the origin of the ray
	t = ray->getOrigin() - v1;

	//Calculating u
	u = glm::dot(t, p) * inv_det;
	if (u < 0.0f || u > 1.0f)
		return false;

	//Calculating v
	q = glm::cross(t, edge1);
	v = glm::dot(ray->getDirection(), q) * inv_det;
	if (v < 0.0f || u + v > 1.0f)
		return false;

	lambda = glm::dot(edge2, q) * inv_det;
	if (lambda > -LAMBDA_TOLERANCE && lambda < LAMBDA_TOLERANCE) {
		ray->getPointAtLambda(lambda, collisionPoint);
		collisionIndex = index;
		return true;
	}

	return false;
}

void CollisionDetector::testCollision()
{
	collided = false;
	for (unsigned int i = 0; i < mesh->getNumberOfIndices(); i += 3) {
		collided = collided || akenineMollerCollisionTest(i);
	}

	/*if (collided) {
		cout << "Houve colisao!" << endl;
		cout << "Ponto de colisao: " << collisionPoint.x << "\t";
		cout << collisionPoint.y << "\t" << collisionPoint.z << endl;
	}
	else {
		cout << "Nao houve colisao" << endl;
	}
	cout << endl;*/
}

bool CollisionDetector::hasCollided()
{
	return collided;
}

vec3& CollisionDetector::getCollisionPoint()
{
	return collisionPoint;
}

unsigned int CollisionDetector::getCollisionIndex()
{
	return collisionIndex;
}
