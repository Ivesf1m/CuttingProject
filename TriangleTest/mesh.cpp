#include "mesh.h"
#include <iostream>

Mesh::Mesh()
     : numberOfVertices(0), numberOfBytes(0)
{

}

Mesh::~Mesh()
{
	//Nothing to delete.
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
