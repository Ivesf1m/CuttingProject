#pragma once

#include <CollisionPath.h>
#include <glm.hpp>
#include <vector>
#include "vertex.h"

using glm::vec3;

class MeshCutter
{
public:
	MeshCutter(CollisionPath* path, vector<Vertex>* vertices,
		vector<unsigned int>* indices, bool internalFirst);
	~MeshCutter();

	void cut();

private:
	CollisionPath* path;
	vector<Vertex>* vertices;
	vector<unsigned int>* indices;
	bool internalFirst;
	unsigned int currentIntermediate1;
	unsigned int currentIntermediate2;

	//Private cutting functions
	bool compareWithError(const vec3& v1, const vec3& v2);
	bool getPointsEdge(const vec3& point, unsigned int triIndex,
		unsigned int& edgeIndex1, unsigned int& edgeIndex2,
		unsigned int& oppositeIndex);

	void cutDifferentEdges(const vec3& entrance, const vec3& internal,
		const vec3& exit, unsigned int triIndex, unsigned int edge1, 
		unsigned int edge2, unsigned int opposite1, unsigned int edge3,
		unsigned int edge4, unsigned int opposite2);
	void cutNoEntrance(const vec3& internal, const vec3& exit, 
		unsigned int triIndex, vec3& intermediate1, vec3& intermediate2);
	void cutNoExit(const vec3& entrance, const vec3& internal,
		unsigned int triIndex);
	void cutSameEdge(const vec3& entrance, const vec3& internal,
		const vec3& exit, unsigned int triIndex, 
		unsigned int edge1, unsigned int edge2,
		unsigned int opposite);
	void regularCut(const vec3& entrance, const vec3& internal,
		const vec3& exit, unsigned int triIndex);
};

