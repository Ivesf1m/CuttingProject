#ifndef MESH_H
#define MESH_H

#include "vertex.h"
#include <vector>

using namespace std;

class Mesh{

    public:
        Mesh();
		virtual ~Mesh();
        void addVertex(const Vertex& v);
        void addVertices(const vector<Vertex>& verts);
        void removeVertex(unsigned int vertexIndex);
        void removeAllVertices();

        const Vertex& getVertex(unsigned int index);
        Vertex* getVertices();
        void setVertex(unsigned int index, const Vertex& vertex);

        unsigned int getNumberOfVertices();
        unsigned int getNumberOfBytes();


    protected:
        unsigned int numberOfVertices;
        unsigned int numberOfBytes;
        vector<Vertex> vertices;
};

#endif // MESH_H



