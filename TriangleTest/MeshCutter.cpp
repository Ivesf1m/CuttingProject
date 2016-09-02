#include "MeshCutter.h"
#include <iostream>

#define EPSILON 1e-5

using std::endl;
using std::cout;

MeshCutter::MeshCutter(CollisionPath * path, vector<Vertex>* vertices,
	vector<unsigned int>* indices, bool internalFirst)
	: path(path), vertices(vertices), indices(indices),
	  internalFirst(internalFirst)
{
}


MeshCutter::~MeshCutter()
{
}

void printVec3(const vec3& v) {
	cout << v.x << "\t" << v.y << "\t" << v.z << endl;
}

void MeshCutter::cut()
{
	//We cannot cut if there are no path, vertice or indices.
	if (!(path && vertices && indices))
		return;
	vec3 entrance, internal, exit;
	unsigned int i = 0;

	//Intermeiate points: the points that are generated on the exit edge.
	vec3 i1, i2;

	if (internalFirst) {
		cout << "entrou no if" << endl;
		//The first point of the path is inside a triangle
		internal = path->getCollisionPoints().at(0);
		exit = path->getCollisionPoints().at(1);
		cutNoEntrance(internal, exit, path->getCollisionIndices().at(0),
			i1, i2);
		i = 1;
	}

	//From now on cuts should follow the pattern
	//entrance (which may be the exit of another cut)
	//internal - exit.
	//The last cut may have no exit.
	for (; i < path->getCollisionPoints().size(); i += 2) {
		entrance = path->getCollisionPoints().at(i);
		internal = path->getCollisionPoints().at(i + 1);
		if (i + 2 >= path->getCollisionPoints().size()) {
			//This is the last part of the cut.
			//i1 and i2 should be defined if we get here.

			cutNoExit(entrance, internal, path->getCollisionIndices().at(i),
				i1, i2);
		}
		else {
			exit = path->getCollisionPoints().at(i + 2);
		}
	}
}

void MeshCutter::cutNoEntrance(const vec3& internal, const vec3& exit,
	unsigned int triIndex, vec3& intermediate1, vec3& intermediate2)
{
	//Getting the edge which contains the exit point
	//and the opposite vertex.
	unsigned int edge1, edge2, opposite;
	bool edgeFound = getPointsEdge(exit, triIndex, edge1, edge2, opposite);

	//If we don't find an edge, we can't proceed with the cut.
	if (!edgeFound)
		return;

	//Get triangle vertices
	Vertex v1 = vertices->at(edge1);
	Vertex v2 = vertices->at(edge2);
	Vertex v3 = vertices->at(opposite);

	//We create a new vertex for the internal points
	Vertex internalPoint(internal, v1.color());

	//Setting the intermediate points.
	vec3 exitEdge = v2.position() - v1.position();
	float length = glm::length(exitEdge);
	exitEdge = glm::normalize(exitEdge);
	intermediate1 = exit - (length / 20.0f) * exitEdge;
	intermediate2 = exit + (length / 20.0f) * exitEdge;

	//We'll have four new triangles
	//First, we need to add the new vertices to
	//the mesh's vector and get their indices.
	unsigned int internalIndex, new1Index, new2Index;
	Vertex new1(intermediate1, v1.color());
	Vertex new2(intermediate2, v1.color());
	vertices->push_back(internalPoint);
	internalIndex = static_cast<unsigned int>(vertices->size() - 1);
	vertices->push_back(new1);
	new1Index = internalIndex + 1;
	vertices->push_back(new2);
	new2Index = new1Index + 1;

	//We now need to overwrite the previous triangle
	//and add the 3 other new ones.

	//First triangle (overwrite)
	(*indices)[triIndex] = internalIndex;
	(*indices)[triIndex + 1] = edge1;
	(*indices)[triIndex + 2] = new1Index;

	//Second triangle
	indices->push_back(internalIndex);
	indices->push_back(new2Index);
	indices->push_back(edge2);
	
	//Third triangle
	indices->push_back(internalIndex);
	indices->push_back(edge2);
	indices->push_back(opposite);

	//Fourth triangle
	indices->push_back(edge1);
	indices->push_back(internalIndex);
	indices->push_back(opposite);
}

void MeshCutter::cutNoExit(const vec3& internal, const vec3& exit,
	unsigned int triIndex, vec3& intermediate1, vec3& intermediate2)
{
	//Getting the edge which contains the exit point
	//and the opposite vertex.
	unsigned int edge1, edge2, opposite;
	bool edgeFound = getPointsEdge(exit, triIndex, edge1, edge2, opposite);

	//If we don't find an edge, we can't proceed with the cut.
	if (!edgeFound)
		return;

	//Get triangle vertices
	Vertex v1 = vertices->at(edge1);
	Vertex v2 = vertices->at(edge2);
	Vertex v3 = vertices->at(opposite);

	//We create a new vertex for the internal points
	Vertex internalPoint(internal, v1.color());

	//We'll have four new triangles
	//First, we need to add the new vertices to
	//the mesh's vector and get their indices.
	//new1 and new2 may be already set.
	unsigned int internalIndex, new1Index, new2Index;
	Vertex new1(intermediate1, v1.color());
	Vertex new2(intermediate2, v1.color());
	vertices->push_back(internalPoint);
	internalIndex = static_cast<unsigned int>(vertices->size() - 1);
	vertices->push_back(new1);
	new1Index = internalIndex + 1;
	vertices->push_back(new2);
	new2Index = new1Index + 1;
}

bool MeshCutter::getPointsEdge(const vec3& point, unsigned int triIndex,
	unsigned int& edgeIndex1, unsigned int& edgeIndex2, unsigned int& oppositeIndex)
{
	//We will be using vector calculus to solve this problem.
	//If the point is on one edge, to cross product of the and
	//a vector from one of the edge's vertices to the point
	//will be zero.
	//Get triangle vertices
	Vertex v1 = vertices->at(indices->at(triIndex));
	Vertex v2 = vertices->at(indices->at(triIndex + 1));
	Vertex v3 = vertices->at(indices->at(triIndex + 2));

	//Triangle edges
	vec3 e1 = v2.position() - v1.position();
	vec3 e2 = v3.position() - v2.position();
	vec3 e3 = v1.position() - v3.position();

	//Test vector
	vec3 test;
	vec3 zeroVector(0.0f, 0.0f, 0.0f);

	//Edge 1
	test = point - v1.position();
	test = glm::cross(test, e1);
	if (compareWithError(test, zeroVector)) {
		edgeIndex1 = indices->at(triIndex);
		edgeIndex2 = indices->at(triIndex + 1);
		oppositeIndex = indices->at(triIndex + 2);
		return true;
	}

	//Edge 2
	test = point - v2.position();
	test = glm::cross(test, e2);
	if (compareWithError(test, zeroVector)) {
		edgeIndex1 = indices->at(triIndex + 1);
		edgeIndex2 = indices->at(triIndex + 2);
		oppositeIndex = indices->at(triIndex);
		return true;
	}

	//Edge 3
	test = point - v3.position();
	test = glm::cross(test, e3);
	if (compareWithError(test, zeroVector)) {
		edgeIndex1 = indices->at(triIndex + 2);
		edgeIndex2 = indices->at(triIndex);
		oppositeIndex = indices->at(triIndex + 1);
		return true;
	}
	
	//None of the 3 edges was a match, so there is an error.
	std::cerr << "O ponto de entrada ou de saida do corte nao esta contido em nenhuma das arestas." << std::endl;
	return false;
}

bool MeshCutter::compareWithError(const vec3& v1, const vec3& v2)
{
	vec3 sub = v2 - v1;
	return (fabs(sub.x) < EPSILON && fabs(sub.y) < EPSILON 
		&& fabs(sub.z) < EPSILON);
}
