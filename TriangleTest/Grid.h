#pragma once
#include "mesh.h"

class Grid : public Mesh
{
public:
	Grid(int dimension);
	virtual ~Grid();

private:
	//Private functions
	void createGrid();

	//Attributes
	int dimension;
};

