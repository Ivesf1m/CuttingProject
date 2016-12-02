#include "MeshCutter.h"
#include <algorithm>
#include <iostream>
#include <utility>

#define EPSILON 1e-5

using std::endl;
using std::cout;
using std::pair;

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
	Vertex v4 = vertices->at(edge3);
	Vertex v5 = vertices->at(edge4);
	Vertex v6 = vertices->at(opposite1);

	//Creating intermediate points. We need 6, 2 for entrance,
	//2 for exit and 2 internally.
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

	//Internal points
	vec3 intermediate5, intermediate6;
	//We need the normal vector
	vec3 n = glm::normalize(glm::cross(v2.position() - v1.position(),
		v3.position() - v2.position()));
	vec3 dir = glm::normalize(internal - entrance);
	vec3 openingDirection = glm::cross(dir, n);
	//Reusing the previous length.
	intermediate5 = internal - (length / 50.0f) * openingDirection;
	intermediate6 = internal + (length / 50.0f) * openingDirection;

	//Adding all the new points.
	Vertex new1(intermediate1, v1.color());
	Vertex new2(intermediate2, v2.color());
	Vertex new3(intermediate3, v3.color());
	Vertex new4(intermediate4, v4.color());
	Vertex new5(intermediate5, v5.color());
	Vertex new6(intermediate6, v6.color());

	unsigned int new1Index, new2Index, new3Index, new4Index, new5Index, new6Index;
	vertices->push_back(new1);
	new1Index = static_cast<unsigned int>(vertices->size() - 1);
	vertices->push_back(new2);
	new2Index = new1Index + 1;
	//The new exit vertices are the currentIntermediates
	vertices->push_back(new3);
	currentIntermediate1 = new3Index = new2Index + 1;
	vertices->push_back(new4);
	currentIntermediate2 = new4Index = new3Index + 1;
	vertices->push_back(new5);
	new5Index = new4Index + 1;
	vertices->push_back(new6);
	new6Index = new5Index + 1;

	/*cout << intermediate1.x << "\t" << intermediate1.y << "\t" << intermediate1.z << endl;
	cout << intermediate2.x << "\t" << intermediate2.y << "\t" << intermediate2.z << endl;
	cout << intermediate3.x << "\t" << intermediate3.y << "\t" << intermediate3.z << endl;
	cout << intermediate4.x << "\t" << intermediate4.y << "\t" << intermediate4.z << endl;
	cout << intermediate5.x << "\t" << intermediate5.y << "\t" << intermediate5.z << endl;
	cout << intermediate6.x << "\t" << intermediate6.y << "\t" << intermediate6.z << endl;*/

	//Now we need to check which vertex from each of the new pairs
	//is closer to the shared vertex.
	vec3 shared = vertices->at(sharedIndex).position();

	float d1, d2, d3, d4, d5, d6;
	unsigned int closerPair1, furtherPair1, closerPair2, furtherPair2;
	unsigned int closerPair3, furtherPair3;
	d1 = glm::distance(intermediate1, shared);
	d2 = glm::distance(intermediate2, shared);
	d3 = glm::distance(intermediate3, shared);
	d4 = glm::distance(intermediate4, shared);
	d5 = glm::distance(intermediate5, shared);
	d6 = glm::distance(intermediate6, shared);

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
		closerPair2 = new3Index;
		furtherPair2 = new4Index;
	}
	else {
		closerPair2 = new4Index;
		furtherPair2 = new3Index;
	}

	//Pair 3
	if (d5 < d5) {
		closerPair3 = new5Index;
		furtherPair3 = new6Index;
	}
	else {
		closerPair3 = new6Index;
		furtherPair3 = new5Index;
	}

	//We now create the new triangles
	//First triangle (overwrite)
	(*indices)[triIndex] = sharedIndex;
	(*indices)[triIndex + 1] = closerPair3;
	(*indices)[triIndex + 2] = closerPair1;

	//Second triangle
	indices->push_back(sharedIndex);
	indices->push_back(closerPair2);
	indices->push_back(closerPair3);

	//Third triangle
	indices->push_back(furtherPair2);
	indices->push_back(opposite1);
	indices->push_back(furtherPair3);

	//Fourth triangle
	indices->push_back(furtherPair3);
	indices->push_back(opposite1);
	indices->push_back(opposite2);

	//Fifth triangle
	indices->push_back(furtherPair1);
	indices->push_back(furtherPair3);
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

	//Creating intermediate points. We need 6, 2 for entrance,
	//2 for exit and 2 internally.
	//For the entrance:
	vec3 intermediate1, intermediate2;
	vec3 sharedEdge = v2.position() - v1.position();
	float length = glm::length(sharedEdge);
	sharedEdge = glm::normalize(sharedEdge);
	intermediate1 = entrance - (length / 50.0f) * sharedEdge;
	intermediate2 = entrance + (length / 50.0f) * sharedEdge;

	//For the exit:
	vec3 intermediate3, intermediate4;
	intermediate3 = exit - (length / 50.0f) * sharedEdge;
	intermediate4 = exit + (length / 50.0f) * sharedEdge;

	//Internal points
	vec3 intermediate5, intermediate6;
	//We need the normal vector
	vec3 n = glm::normalize(glm::cross(v2.position() - v1.position(),
		v3.position() - v2.position()));
	vec3 dir = glm::normalize(internal - entrance);
	vec3 openingDirection = glm::cross(dir, n);
	//Reusing the previous length.
	intermediate5 = internal - (length / 50.0f) * openingDirection;
	intermediate6 = internal + (length / 50.0f) * openingDirection;

	//Adding all the new points.
	Vertex new1(intermediate1, v1.color());
	Vertex new2(intermediate2, v2.color());
	Vertex new3(intermediate3, v3.color());
	Vertex new4(intermediate4, v1.color());
	Vertex new5(intermediate5, v2.color());
	Vertex new6(intermediate6, v3.color());

	unsigned int new1Index, new2Index, new3Index, new4Index, new5Index, new6Index;
	vertices->push_back(new1);
	new1Index = static_cast<unsigned int>(vertices->size() - 1);
	vertices->push_back(new2);
	new2Index = new1Index + 1;
	//The new exit vertices are the currentIntermediates
	vertices->push_back(new3);
	currentIntermediate1 = new3Index = new2Index + 1;
	vertices->push_back(new4);
	currentIntermediate2 = new4Index = new3Index + 1;
	vertices->push_back(new5);
	new5Index = new4Index + 1;
	vertices->push_back(new6);
	new6Index = new5Index + 1;

	//Now we need to find out to which vertex the entrance is closer.
	unsigned int closerToEntrance, closerToExit;
	float dv1 = glm::distance(entrance, v1.position());
	float dv2 = glm::distance(entrance, v2.position());

	vec3 closerPoint;

	if (dv1 < dv2) {
		closerToEntrance = edge1;
		closerToExit = edge2;
		closerPoint = v1.position();
	}
	else {
		closerToEntrance = edge2;
		closerToExit = edge1;
		closerPoint = v2.position();
	}

	float d1 = glm::distance(closerPoint, intermediate1);
	float d2 = glm::distance(closerPoint, intermediate2);
	float d3 = glm::distance(closerPoint, intermediate3);
	float d4 = glm::distance(closerPoint, intermediate4);

	//Sorting these points
	pair<unsigned int, float> pair1(new1Index, d1);
	pair<unsigned int, float> pair2(new2Index, d2);
	pair<unsigned int, float> pair3(new3Index, d3);
	pair<unsigned int, float> pair4(new4Index, d4);
	vector< pair<unsigned int, float> > pairVec;
	pairVec.push_back(pair1);
	pairVec.push_back(pair2);
	pairVec.push_back(pair3);
	pairVec.push_back(pair4);

	std::sort(pairVec.begin(), pairVec.end(), [](auto& left, auto& right) {
		return left.second < right.second;
	});

	//Now we find out which of the new internal points is closer to the edge
	vec3 p1 = v1.position();
	//Remember sharedEdge is the normalized direction of the edge, from v1 to v2.
	vec3 p1i5 = intermediate5 - p1;
	vec3 p1i6 = intermediate6 - p1;
	float dist1 = glm::length(p1i5 - (glm::dot(p1i5, sharedEdge) * sharedEdge));
	float dist2 = glm::length(p1i6 - (glm::dot(p1i6, sharedEdge) * sharedEdge));
	unsigned int closerToEdge, furtherFromEdge;
	if (dist1 < dist2) {
		closerToEdge = new5Index;
		furtherFromEdge = new6Index;
	}
	else {
		closerToEdge = new6Index;
		furtherFromEdge = new5Index;
	}

	//We now need to overwrite the previous triangle
	//and add the 4 other new ones.

	//First triangle (overwrite)
	(*indices)[triIndex] = pairVec[1].first;
	(*indices)[triIndex + 1] = closerToEdge;
	(*indices)[triIndex + 2] = pairVec[2].first;

	//Second triangle
	indices->push_back(closerToEntrance);
	indices->push_back(pairVec[0].first);
	indices->push_back(furtherFromEdge);

	//Third triangle
	indices->push_back(closerToEntrance);
	indices->push_back(furtherFromEdge);
	indices->push_back(opposite);

	//Fourth triangle
	indices->push_back(pairVec[3].first);
	indices->push_back(closerToExit);
	indices->push_back(furtherFromEdge);

	//Fifth triangle
	indices->push_back(closerToExit);
	indices->push_back(opposite);
	indices->push_back(furtherFromEdge);
}

void MeshCutter::regularCut(const vec3& entrance, const vec3& internal,
	const vec3& exit, unsigned int triIndex)
{
	//We need to find out if the entrance and exit vertices are on the same
	//edge.
	unsigned int edge1, edge2, opposite;
	bool edgeFound = getPointsEdge(entrance, triIndex, edge1, edge2, opposite);

	if (!edgeFound)
		return;

	unsigned int edge3, edge4, opposite2;
	edgeFound = getPointsEdge(exit, triIndex, edge3, edge4, opposite2);

	if (!edgeFound)
		return;

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
	//If the point is on one edge, the cross product of the edge and
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
	std::cerr << point.x << "\t" << point.y << "\t" << point.z << endl;
	return false;
}

bool MeshCutter::compareWithError(const vec3& v1, const vec3& v2)
{
	vec3 sub = v2 - v1;
	return (fabs(sub.x) < EPSILON && fabs(sub.y) < EPSILON 
		&& fabs(sub.z) < EPSILON);
}
