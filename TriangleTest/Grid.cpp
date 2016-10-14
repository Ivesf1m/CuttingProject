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

void Grid::checkVector(vector<vec3>& vMap, vec3 vertex, 
	unsigned int& index)
{
	static vec3 defaultColor(1.0f, 0.0f, 0.0f);
	bool aux = false;
	for (unsigned int i = 0; i < vMap.size(); ++i) {
		if (vMap[i] == vertex) {
			aux = true;
			index = i;
		}
	}

	if (!aux) {
		vMap.push_back(vertex);
		addVertex(Vertex(vertex, defaultColor));
		index = static_cast<unsigned int>(vMap.size()) - 1;
	}
}

void Grid::createGrid()
{
	if (this->dimension <= 0) {
		cerr << "Error: grid dimension cannot be 0 or negative." << endl;
		exit(1);
	}
	float z = 0.0f;	

	vector<vec3> vertexVector;

	//Creating a grid of size dimension x dimension
	for (float i = 0.0f; i < dimension; ++i) {
		for (float j = 0.0f; j < dimension; ++j) {
			//We are adding a square to the grid at each iteration,
			//which means two new triangles.
			vec3 v1(i, j, z);
			vec3 v2(i + 1.0f, j, z);
			vec3 v3(i, j + 1.0f, z);
			vec3 v4(i + 1.0f, j + 1.0f, z);
			unsigned int i1, i2, i3, i4; //indices

			//Checking if these vertices were already created in previous
			//iterations. If not, they are added to the mesh.
			checkVector(vertexVector, v1, i1);
			checkVector(vertexVector, v2, i2);
			checkVector(vertexVector, v3, i3);
			checkVector(vertexVector, v4, i4);

			//Adding indices
			//First triangle
			this->addTriangularFace(i1, i2, i3);

			//Second triangle
			this->addTriangularFace(i2, i4, i3);
		}
	}
	cout << "Numero de vertices: " << getNumberOfVertices() << endl;
	cout << "Numero de indices: " << getNumberOfIndices() << endl;
}
