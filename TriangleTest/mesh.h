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

		void addTriangularFace(unsigned int index1, unsigned int index2,
			unsigned int index3);

		//Removes three indices from the index vector, starting at
		//the index at pos.
		void removeTriangularFace(unsigned int pos);
		void removeAllIndices();

        const Vertex& getVertex(unsigned int index);
        Vertex* getVertices();
        void setVertex(unsigned int index, const Vertex& vertex);
		unsigned int* getIndices();

        unsigned int getNumberOfVertices();
        unsigned int getNumberOfBytes();
		unsigned int getNumberOfIndices();

    protected:
        unsigned int numberOfVertices;
        unsigned int numberOfBytes;
		unsigned int numberOfIndices;
        vector<Vertex> vertices;
		vector<unsigned int> indices;
};

#endif // MESH_H



