#ifndef MESH_H
#define MESH_H

#include "CollisionPath.h"
#include "vertex.h"
#include <vector>
#include <MeshCutter.h>

using namespace std;

class Mesh{

    public:
        Mesh();
		virtual ~Mesh();

        void addVertex(const Vertex& v);
        void addVertices(const vector<Vertex>& verts);
        void removeVertex(unsigned int vertexIndex);
        void removeAllVertices();

		void loadFromObjFile(string& fileName);
		void printMeshInfo();

		void addTriangularFace(unsigned int index1, unsigned int index2,
			unsigned int index3);

		//Removes three indices from the index vector, starting at
		//the index at pos.
		void removeTriangularFace(unsigned int pos);
		void removeAllIndices();

        const Vertex& getVertex(unsigned int index);
        Vertex* getVertices();
		vector<Vertex>& getVertexVector();
		vector<unsigned int>& getIndexVector();
        void setVertex(unsigned int index, const Vertex& vertex);
		unsigned int getIndex(unsigned int index);
		unsigned int* getIndices();

        unsigned int getNumberOfVertices();
        unsigned int getNumberOfBytes();
		unsigned int getNumberOfIndices();

		void cut(CollisionPath& path);

    protected:
        unsigned int numberOfVertices;
        unsigned int numberOfBytes;
		unsigned int numberOfIndices;
        vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector< vector<unsigned int> > neighbors;

		void removeNeighborDuplicates();
		void findEdgePoint(unsigned int index1, unsigned int index2,
			const vec3 colPoint, const vec3& dir, vec3& exitPoint);
		void updateMesh(CollisionPath& path, bool internalFirst);
};

#endif // MESH_H



