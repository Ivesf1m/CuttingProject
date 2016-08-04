#include "Grid.h"



Grid::Grid(int dimension)
	: dimension(dimension)
{
	createGrid();
}


Grid::~Grid()
{
	//Nothing to delete
}

void Grid::createGrid()
{
	if (this->dimension <= 0) {
		cerr << "Error: grid dimension cannot be 0 or negative." << endl;
		exit(1);
	}
	float z = 1.0f;
	//Default color
	vec3 defaultColor(1.0f, 0.0f, 0.0f);

	//Creating a grid of size dimension x dimension
	for (float i = 0.0f; i < dimension; ++i) {
		for (float j = 0.0f; j < dimension; ++j) {
			//We are adding a square to the grid at each iteration,
			//which means two new triangles.
			vec3 v1(i, j, z);
			vec3 v2(i + 1.0f, j, z);
			vec3 v3(i, j + 1.0f, z);
			vec3 v4(i + 1.0f, j + 1.0f, z);

			//First triangle
			addVertex(Vertex(v1, defaultColor));
			addVertex(Vertex(v2, defaultColor));
			addVertex(Vertex(v3, defaultColor));

			//Second triangle
			addVertex(Vertex(v2, defaultColor));
			addVertex(Vertex(v4, defaultColor));
			addVertex(Vertex(v3, defaultColor));
		}
	}
}
