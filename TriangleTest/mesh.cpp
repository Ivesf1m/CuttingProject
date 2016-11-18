#include "mesh.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::ifstream;
using std::stringstream;

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

void Mesh::loadFromObjFile(string& fileName)
{
	ifstream stream(fileName);
	if (!stream.good()) {
		cerr << "Falha no carregamento do modelo " << fileName << endl;
		exit(1);
	}

	bool normalFound = false;

	vector<vec3> faceNormals;
	vector< vector<int> > sharedNormals;
	static vec3 defaultColor(1.0f, 0.0f, 0.0f);

	while (!stream.eof()) {
		//first word of each line
		// v for vertices
		// vn for face normals - we need to calculate vertex normals
		// f for faces
		string identifier;
		stream >> identifier;
		if (identifier.compare("v") == 0) {
			vec3 coords;
			stream >> coords.x >> coords.y >> coords.z;
			Vertex newVertex(coords);
			//We're setting red as the default color.
			newVertex.setColor(defaultColor);
			addVertex(newVertex);			

			//Every vertex need a list of neighbors and will have shared normals
			sharedNormals.push_back(vector<int>());
			neighbors.push_back(vector<unsigned int>());
		}
		else if (identifier.compare("vn") == 0) {
			normalFound = true;
			vec3 normal;
			stream >> normal.x >> normal.y >> normal.z;
			faceNormals.push_back(normal);
		}
		else if (identifier.compare("f") == 0) {
			//If the file has normals, we are going to read tuples
			//with format 0//0. Else there will be only the vertex
			//index.
			int index1, index2, index3;
			if (normalFound) {
				int n1, n2, n3; //normals
				char slash;
				stream >> index1 >> slash >> slash >> n1;
				stream >> index2 >> slash >> slash >> n2;
				stream >> index3 >> slash >> slash >> n3;
				addTriangularFace(--index1, --index2, --index3);

				//We're using these to calculate vertex normals later.
				sharedNormals[index1].push_back(--n1);
				sharedNormals[index2].push_back(--n2);
				sharedNormals[index3].push_back(--n3);
			}
			else {
				stream >> index1 >> index2 >> index3;
				addTriangularFace(--index1, --index2, --index3);
			}

			//Neighbors
			neighbors[index1].push_back(index2);
			neighbors[index1].push_back(index3);
			neighbors[index2].push_back(index1);
			neighbors[index2].push_back(index3);
			neighbors[index3].push_back(index1);
			neighbors[index3].push_back(index2);

		}
		else {
			char line[256];
			stream.getline(line, 256);
		}
	}

	//Calculate vertex normals
	calculateVertexNormals(faceNormals, sharedNormals);

	//Remove duplicated from neighbor vectors.
	removeNeighborDuplicates();

	//printMeshInfo();
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

unsigned int Mesh::getIndex(unsigned int index)
{
	if (index > indices.size()) {
		cerr << "Invalid face index" << endl;
		exit(1);
	}

	return indices[index];
}

unsigned int* Mesh::getIndices()
{
	return &(indices[0]);
}

void Mesh::findEdgePoint(unsigned int index1, unsigned int index2,
	const vec3 colPoint, const vec3& dir, vec3& exitPoint)
{
	//Getting the indices for each triangle
	//The actual vertex indices.
	unsigned int t1i1 = indices[index1];
	unsigned int t1i2 = indices[index1 + 1];
	unsigned int t1i3 = indices[index1 + 2];

	unsigned int t2i1 = indices[index2];
	unsigned int t2i2 = indices[index2 + 1];
	unsigned int t2i3 = indices[index2 + 2];

	//We need to check which vertices are shared by these triangles.
	unsigned shared1, shared2;
	if (t1i1 == t2i1) {
		shared1 = t1i1;
		if (t1i2 == t2i2 || t1i2 == t2i3)
			shared2 = t1i2;
		else shared2 = t1i3;
	}
	else if (t1i1 == t2i2) {
		shared1 = t1i1;
		if (t1i2 == t2i1 || t1i2 == t2i3)
			shared2 = t1i2;
		else shared2 = t1i3;
	}
	else if (t1i1 == t2i3) {
		if (t1i2 == t2i2 || t1i2 == t2i1)
			shared2 = t1i2;
		else shared2 = t1i3;
	}
	else {
		shared1 = t1i2;
		shared2 = t1i3;
	}

	//Now we need to find the point on the edge which is
	//crossed.
	//To do that we solve the equation
	//lambda1 * d1 = (O2 - O1) + lambda2 * d2
	//by applying the cross product with d2 on both sides.
	//lambda1 * (d1 x d2) = (O2 - O1) x d2
	vec3 d1 = glm::normalize(vertices[shared2].position() - 
		vertices[shared1].position());
	vec3 d1d2 = glm::cross(d1, dir);
	vec3 rightSide = colPoint - vertices[shared1].position();
	rightSide = glm::cross(rightSide , dir);

	//Right side and d1d2 should be parallel and different
	//to the zero factor. They should differ by a lambda factor
	//and that's the solution of the equation.
	float lambda;
	if (d1d2.x != 0)
		lambda = rightSide.x / d1d2.x;
	else if(d1d2.y != 0)
		lambda = rightSide.y / d1d2.y;
	else if (d1d2.z != 0)
		lambda = rightSide.z / d1d2.z;

	//If no lambda satisfied the 0 condition, the exitPoint will be
	//one of the vertices of the triangle.
	exitPoint = vertices[shared1].position() + lambda * d1;
	

}

void Mesh::cut(CollisionPath& path)
{
	if (path.getNumberOfPoints() == 0)
		return;

	cout << "Number of collision points: " << path.getNumberOfPoints() << endl;

	//We need to find out where the collisionPath crosses to different triangles
	//The indices stored here are indices for the vector stored in the mesh,
	//not the actual vertex indices.
	vector<unsigned int>& colIndices = path.getCollisionIndices();
	vector<vec3>& colPoints = path.getCollisionPoints();
	vec3 direction;
	vec3 exitPoint;
	vector<vec3> exitPoints;
	vector<unsigned int> internalPoints;
	bool internalFirst = false;

	//We process the path passed as parameter so we generate a new 
	//simplified path.
	//We do this by selecting one internal point for each triangle
	//and figuring out the exit Point (which, in turn, will be the next
	//entrance point).
	CollisionPath newPath;
	bool dirFound = false;
	bool otherInternal = false;
	for (unsigned int i = 0; i < colIndices.size(); ++i) {
		if (i + 1 >= colIndices.size()) {
			//This is the last point
			internalPoints.push_back(colIndices[i]);
		}
		else if (colIndices[i] != colIndices[i + 1]) {			
			if (!dirFound) {
				//We need the normal of the first triangle
				//Edges os the triangle (v2 - v1) and (v3 - v2)
				vec3 e1 = vertices[indices[colIndices[i] + 1]].position()
					- vertices[indices[colIndices[i]]].position();
				vec3 e2 = vertices[indices[colIndices[i] + 2]].position()
					- vertices[indices[colIndices[i] + 1]].position();
				//Normalized normal vector
				vec3 normal = glm::normalize(glm::cross(e1, e2));
				//Vector from the first collisionPoint to the second
				vec3 aux = colPoints[i + 1] - colPoints[i];
				//Now we project this vector onto the first triangle
				//and use it as the direction of the cut.
				//We don't need to divide te dot product by the length
				//of the normal, because it is normalized.
				direction = aux - (glm::dot(aux, normal) * normal);
				direction = glm::normalize(direction);
			}
			findEdgePoint(colIndices[i], colIndices[i + 1], colPoints[i], 
				direction, exitPoint);

			//If the exit point is one of the collision points
			//and an internal point has not been found preivously
			//the exit point is the first one on the list.
			if (exitPoint != colPoints[i] && !internalFirst)
				internalFirst = true;

			//If there is only one internal point for this triangle
			//we need to add it to the vector here.
			if (!otherInternal)
				internalPoints.push_back(colIndices[i]);
				
			dirFound = false;
			exitPoints.push_back(exitPoint);
		}
		else {
			if (!dirFound) {
				direction = glm::normalize(colPoints[i + 1] - colPoints[i]);
				dirFound = true;
				if (internalPoints.size() == 0 && exitPoints.size() == 0)
					internalFirst = true;
				internalPoints.push_back(colIndices[i]);
				
			}
			otherInternal = true;
		}
	}

	size_t size = (internalPoints.size() > exitPoints.size() ?
		internalPoints.size() : exitPoints.size());
	for (size_t i = 0; i < size; ++i) {
		if (internalFirst) {
			if (i < internalPoints.size()) {
				newPath.addPoint(colPoints[i]);
				newPath.addIndex(internalPoints[i]);
			}

			if (i < exitPoints.size()) {
				newPath.addPoint(exitPoints[i]);
				newPath.addIndex(internalPoints[i]);
			}
		}
		else {
			//We add the points to the path in a different order.
			if (i < exitPoints.size()) {
				newPath.addPoint(exitPoints[i]);
				newPath.addIndex(internalPoints[i]);
			}

			if (i < internalPoints.size()) {
				newPath.addPoint(colPoints[i]);
				newPath.addIndex(internalPoints[i]);
			}
		}
	}
	updateMesh(newPath, internalFirst);

	//Clearing the path
	path.removeAllIndices();
	path.removeAllPoints();
}

void Mesh::updateMesh(CollisionPath& path, bool internalFirst)
{
	MeshCutter cutter(&path, &vertices, &indices, internalFirst);
	cutter.cut();

	numberOfVertices = static_cast<unsigned int>(vertices.size());
	numberOfIndices = static_cast<unsigned int>(indices.size());
	numberOfBytes = numberOfVertices * sizeof(Vertex);

	cout << "Number of vertices: " << numberOfVertices << endl;
	cout << "Number of indices: " << numberOfIndices << endl;
	cout << "Number of bytes: " << numberOfBytes << endl;
}

//Average face normals shared by a vertex to find its own normal.
void Mesh::calculateVertexNormals(vector<vec3>& faceNormals,
	vector< vector<int> >& sharedNormals)
{
	for (unsigned int i = 0; i < sharedNormals.size(); ++i) {
		double xsum = 0.0, ysum = 0.0, zsum = 0.0;
		for (unsigned int j = 0; j < sharedNormals[i].size(); ++j) {
			xsum += faceNormals[sharedNormals[i][j]].x;
			ysum += faceNormals[sharedNormals[i][j]].y;
			zsum += faceNormals[sharedNormals[i][j]].z;
		}

		xsum /= sharedNormals[i].size();
		ysum /= sharedNormals[i].size();
		zsum /= sharedNormals[i].size();

		vec3 normal(xsum, ysum, zsum);
		normal = glm::normalize(normal);
		vertices[i].setNormal(normal);
	}
}

//Helper function to check if a number is in a vector
bool contains(vector<unsigned int> list, unsigned int number)
{
	for (auto element : list) {
		if (element == number)
			return true;
	}
	return false;
}

void Mesh::removeNeighborDuplicates()
{
	for (auto neighborList : neighbors) {
		vector<unsigned int> uniqueList;
		for (auto neighborIndex : neighborList) {
			if (!contains(uniqueList, neighborIndex))
				uniqueList.push_back(neighborIndex);
		}
		neighborList = uniqueList;
	}
}

void Mesh::printMeshInfo()
{
	cout << "Vertices: " << endl;
	for (auto vertex : vertices) {
		vertex.printInfo();
		cout << endl;
	}

	cout << "Faces: " << endl;
	for (unsigned int i = 0; i < indices.size(); i += 3) {
		cout << indices[i] << "\t" << indices[i + 1] << "\t" <<
			indices[i + 2] << endl;
	}
}
