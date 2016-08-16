#pragma once

#include "mesh.h"
#include <map>

using std::map;

class Grid : public Mesh
{
public:
	Grid(int dimension);
	virtual ~Grid();

private:
	//Private functions
	void createGrid();
	void checkVector(vector<vec3>& vMap, vec3 vertex,
		unsigned int& index);

	//Attributes
	int dimension;
};

