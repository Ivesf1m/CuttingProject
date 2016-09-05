#include "MeshCutter.h"
#include <iostream>

#define EPSILON 1e-5

using std::endl;
using std::cout;

MeshCutter::MeshCutter(CollisionPath * path, vector<Vertex>* vertices,
	vector<unsigned int>* indices, bool internalFirst)
	: path(path), vertices(vertices), indices(indices),
	  internalFirst(internalFirst), currentIntermediate1(0),
	currentIntermediate2(0)
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
	for (; i < path->getCollisionPoints().size(); ++i) {
		entrance = path->getCollisionPoints().at(i);

		if (i + 1 >= path->getCollisionPoints().size()) {
			//The cut should end here.
			break;
		}

		internal = path->getCollisionPoints().at(i + 1);

		if (i + 2 >= path->getCollisionPoints().size()) {
			//This is the last part of the cut.
			//i1 and i2 should be defined if we get here.

			cutNoExit(entrance, internal, path->getCollisionIndices().at(i + 1));
		}
		else {
			exit = path->getCollisionPoints().at(i + 2);
			regularCut(entrance, internal, exit, 
				path->getCollisionIndices().at(i + 1));

			//Because we consumed two additional points if we get here,
			//we increment the counter
			++i;
		}
	}

	/*(for (int i = 0; i < vertices->size(); ++i)
		printVec3(vertices->at(i).position());

	for (int i = 0; i < indices->size(); ++i)
		cout << indices->at(i) << endl;*/

}

void MeshCutter::cutDifferentEdges(const vec3& entrance, const vec3& internal,
	const vec3& exit, unsigned int triIndex, unsigned int edge1,
	unsigned int edge2, unsigned int opposite1, unsigned int edge3,
	unsigned int edge4, unsigned int opposite2)
{
	//We need to first find the vertex that is shared by both edges.
	//It is the one that is not opposite to either.
	unsigned int sharedIndex;
	if (edge1 == opposite2)
		sharedIndex = edge2;
	else sharedIndex = edge1;

	//Get triangle vertices (by entrance parameters)
	Vertex v1 = vertices->at(edge1);
	Vertex v2 = vertices->at(edge2);
	Vertex v3 = vertices->at(opposite1);

	//Get triangle vertices (by exit parameters)
	Vertex v4 = vertices->at(edge1);
	Vertex v5 = vertices->at(edge2);
	Vertex v6 = vertices->at(opposite1);

	//We now create the vertex for the internal point.
	Vertex internalPoint(internal, v1.color());

	//Creating intermediate points. We need 4, 2 for entrance,
	//2 for exit.
	//For the entrance:
	vec3 intermediate1, intermediate2;
	vec3 entranceEdge = v2.position() - v1.position();
	float length = glm::length(entranceEdge);
	entranceEdge = glm::normalize(entranceEdge);
	intermediate1 = entrance - (length / 50.0f) * entranceEdge;
	intermediate2 = entrance + (length / 50.0f) * entranceEdge;

	//For the exit:
	vec3 intermediate3, intermediate4;
	vec3 exitEdge = v5.position() - v4.position();
	length = glm::length(exitEdge);
	exitEdge = glm::normalize(exitEdge);
	intermediate3 = exit - (length / 50.0f) * exitEdge;
	intermediate4 = exit + (length / 50.0f) * exitEdge;

	//Adding all the new points.
	Vertex new1(intermediate1, v1.color());
	Vertex new2(intermediate2, v2.color());
	Vertex new3(intermediate3, v3.color());
	Vertex new4(intermediate4, v4.color());

	unsigned int internalIndex, new1Index, new2Index;
	vertices->push_back(internalPoint);
	internalIndex = static_cast<unsigned int>(vertices->size() - 1);
	vertices->push_back(new1);
	new1Index = internalIndex + 1;
	vertices->push_back(new2);
	new2Index = new1Index + 1;
	vertices->push_back(new3);
	currentIntermediate1 = new2Index + 1;
	vertices->push_back(new4);
	currentIntermediate2 = currentIntermediate1 + 1;

	//Now we need to check which vertex from each of the new pairs
	//is closer to the shared vertex.
	vec3 shared = vertices->at(sharedIndex).position();

	float d1, d2, d3, d4;
	unsigned int closerPair1, furtherPair1, closerPair2, furtherPair2;
	d1 = glm::distance(intermediate1, shared);
	d2 = glm::distance(intermediate2, shared);
	d3 = glm::distance(intermediate3, shared);
	d4 = glm::distance(intermediate4, shared);

	//Pair 1
	if (d1 < d2) {
		closerPair1 = new1Index;
		furtherPair1 = new2Index;
	}
	else {
		closerPair1 = new2Index;
		furtherPair1 = new1Index;
	}

	//Pair 2
	if (d3 < d4) {
		closerPair2 = currentIntermediate1;
		furtherPair2 = currentIntermediate2;
	}
	else {
		closerPair2 = currentIntermediate2;
		furtherPair2 = currentIntermediate1;
	}

	//We now create the new triangles
	//First triangle (overwrite)
	(*indices)[triIndex] = sharedIndex;
	(*indices)[triIndex + 1] = internalIndex;
	(*indices)[triIndex + 2] = closerPair1;

	//Second triangle
	indices->push_back(sharedIndex);
	indices->push_back(closerPair2);
	indices->push_back(internalIndex);

	//Third triangle
	indices->push_back(furtherPair2);
	indices->push_back(opposite1);
	indices->push_back(internalIndex);

	//Fourth triangle
	indices->push_back(internalIndex);
	indices->push_back(opposite1);
	indices->push_back(opposite2);

	//Fifth triangle
	indices->push_back(furtherPair1);
	indices->push_back(internalIndex);
	indices->push_back(opposite2);

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
	intermediate1 = exit - (length / 50.0f) * exitEdge;
	intermediate2 = exit + (length / 50.0f) * exitEdge;

	//We'll have four new triangles
	//First, we need to add the new vertices to
	//the mesh's vector and get their indices.
	unsigned int internalIndex;
	Vertex new1(intermediate1, v1.color());
	Vertex new2(intermediate2, v1.color());
	vertices->push_back(internalPoint);
	internalIndex = static_cast<unsigned int>(vertices->size() - 1);

	//Because we are exiting an edge, we need to create new vertices,
	//so we add their indices to the mesh.
	vertices->push_back(new1);
	currentIntermediate1 = internalIndex + 1;
	vertices->push_back(new2);
	currentIntermediate2 = currentIntermediate1 + 1;

	//We now need to overwrite the previous triangle
	//and add the 3 other new ones.

	//First triangle (overwrite)
	(*indices)[triIndex] = internalIndex;
	(*indices)[triIndex + 1] = edge1;
	(*indices)[triIndex + 2] = currentIntermediate1;

	//Second triangle
	indices->push_back(internalIndex);
	indices->push_back(currentIntermediate2);
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

void MeshCutter::cutNoExit(const vec3& entrance, const vec3& internal,
	unsigned int triIndex)
{
	//Getting the edge which contains the exit point
	//and the opposite vertex.
	unsigned int edge1, edge2, opposite;
	bool edgeFound = getPointsEdge(entrance, triIndex, edge1, edge2, opposite);

	//If we don't find an edge, we can't proceed with the cut.
	if (!edgeFound)
		return;

	//Get triangle vertices
	Vertex v1 = vertices->at(edge1);
	Vertex v2 = vertices->at(edge2);
	Vertex v3 = vertices->at(opposite);

	//We create a new vertex for the internal points
	Vertex internalPoint(internal, v1.color());

	//We'll have four new triangles First, we need to add the new vertices to
	//the mesh's vector and get their indices. Because there is no exit here,
	//we are not creating new vertices, we just use the current intermediates.
	unsigned int internalIndex;
	vertices->push_back(internalPoint);
	internalIndex = static_cast<unsigned int>(vertices->size() - 1);

	//We now need to overwrite the previous triangle
	//and add the 3 other new ones.

	//First triangle (overwrite)
	(*indices)[triIndex] = internalIndex;
	(*indices)[triIndex + 1] = edge2;
	(*indices)[triIndex + 2] = currentIntermediate1;

	//Second triangle
	indices->push_back(internalIndex);
	indices->push_back(currentIntermediate2);
	indices->push_back(edge1);

	//Third triangle
	indices->push_back(internalIndex);
	indices->push_back(edge2);
	indices->push_back(opposite);

	//Fourth triangle
	indices->push_back(edge1);
	indices->push_back(internalIndex);
	indices->push_back(opposite);
}

void MeshCutter::cutSameEdge(const vec3& entrance, const vec3& internal,
	const vec3& exit, unsigned int triIndex, unsigned int edge1,
	unsigned int edge2, unsigned int opposite)
{
	//Get triangle vertices
	Vertex v1 = vertices->at(edge1);
	Vertex v2 = vertices->at(edge2);
	Vertex v3 = vertices->at(opposite);

	//We create a new vertex for the entrance, internal and exit points
	Vertex internalPoint(internal, v1.color());
	Vertex entrancePoint(entrance, v1.color());
	Vertex exitPoint(exit, v1.color());

	//We'll have four new triangles. No new vertices need to
	//be created here, we just add internal, entrance and exit.
	unsigned int internalIndex, entranceIndex, exitIndex;
	vertices->push_back(internalPoint);
	internalIndex = static_cast<unsigned int>(vertices->size() - 1);
	vertices->push_back(entrancePoint);
	entranceIndex = internalIndex + 1;
	vertices->push_back(exitPoint);
	exitIndex = entranceIndex + 1;

	//Now we need to find out to which vertex the entrance is closer.
	unsigned int closerToEntrance, closerToExit;
	float d1 = glm::distance(entrance, v1.position());
	float d2 = glm::distance(entrance, v2.position());

	if (d1 < d2) {
		closerToEntrance = edge1;
		closerToExit = edge2;
	}
	else {
		closerToEntrance = edge2;
		closerToExit = edge1;
	}

	//We now need to overwrite the previous triangle
	//and add the 3 other new ones.

	//First triangle (overwrite)
	(*indices)[triIndex] = internalIndex;
	(*indices)[triIndex + 1] = closerToEntrance;
	(*indices)[triIndex + 2] = entranceIndex;

	//Second triangle
	indices->push_back(internalIndex);
	indices->push_back(exitIndex);
	indices->push_back(closerToExit);

	//Third triangle
	indices->push_back(internalIndex);
	indices->push_back(closerToExit);
	indices->push_back(opposite);

	//Fourth triangle
	indices->push_back(closerToEntrance);
	indices->push_back(internalIndex);
	indices->push_back(opposite);
}

void MeshCutter::regularCut(const vec3& entrance, const vec3& internal,
	const vec3& exit, unsigned int triIndex)
{
	//We need to find out if the entrance and exit vertices are on the same
	//edge.
	unsigned int edge1, edge2, opposite;
	bool edgeFound = getPointsEdge(entrance, triIndex, edge1, edge2, opposite);

	unsigned int edge3, edge4, opposite2;
	edgeFound = getPointsEdge(exit, triIndex, edge3, edge4, opposite2);

	//They are on the same edge if they have the same opposite vertex.
	if (opposite == opposite2)
		cutSameEdge(entrance, internal, exit, triIndex,
			edge1, edge2, opposite);
	else
		cutDifferentEdges(entrance, internal, exit, triIndex,
			edge1, edge2, opposite, edge3, edge4, opposite2);
	
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
