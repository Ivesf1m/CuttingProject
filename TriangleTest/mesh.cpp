#include "mesh.h"
#include <iostream>

Mesh::Mesh()
     : numberOfVertices(0), numberOfBytes(0), numberOfIndices(0)
{

}

Mesh::~Mesh()
{
	//Nothing to delete.
}

void Mesh::addTriangularFace(unsigned int index1, unsigned int index2,
	unsigned int index3)
{
	if (index1 >= numberOfVertices || index2 >= numberOfVertices ||
		index3 >= numberOfVertices) {
		cerr << "Error: cannot add index of vertex that does not exist." << endl;
		return;
	}

	indices.push_back(index1);
	indices.push_back(index2);
	indices.push_back(index3);

	numberOfIndices += 3;
}

void Mesh::removeTriangularFace(unsigned int pos)
{
	if (pos >= indices.size() - 3) {
		cerr << "Cannot remove face starting at position " << pos << endl;
		return;
	}
	indices.erase(indices.begin() + pos);
	indices.erase(indices.begin() + pos + 1);
	indices.erase(indices.begin() + pos + 2);

	numberOfIndices -= 3;
}

void Mesh::removeAllIndices()
{
	indices.clear();
	numberOfIndices = 0;
}

void Mesh::addVertex(const Vertex& v)
{
    vertices.push_back(v);
    ++numberOfVertices;
    numberOfBytes += sizeof(Vertex);
}

void Mesh::addVertices(const vector<Vertex>& verts)
{
    for(unsigned int i = 0; i < verts.size(); ++i)
        addVertex(verts[i]);
}

void Mesh::removeVertex(unsigned int vertexIndex)
{
    if(vertexIndex >= vertices.size())
        return;
    vertices.erase(vertices.begin() + vertexIndex);
    --numberOfVertices;
    numberOfBytes -= sizeof(Vertex);
}

void Mesh::removeAllVertices()
{
    vertices.clear();
    numberOfBytes = 0;
    numberOfVertices = 0;
}

const Vertex& Mesh::getVertex(unsigned int index)
{
    if(index >= vertices.size()){
        cerr << "Invalid vertex index" << endl;
        exit(1);
    }
    return vertices[index];
}

Vertex* Mesh::getVertices()
{
    return &(vertices[0]);
}

void Mesh::setVertex(unsigned int index, const Vertex& vertex)
{
    if(index >= vertices.size()){
        cerr << "Invalid vertex index" << endl;
        exit(1);
    }
    vertices[index] = vertex;
}

unsigned int Mesh::getNumberOfVertices()
{
    return numberOfVertices;
}

unsigned int Mesh::getNumberOfBytes()
{
    return numberOfBytes;
}

unsigned int Mesh::getNumberOfIndices()
{
	return numberOfIndices;
}

unsigned int* Mesh::getIndices()
{
	return &(indices[0]);
}
