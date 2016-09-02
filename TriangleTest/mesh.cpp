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
	for (unsigned int i = 0; i < colIndices.size() - 1; ++i) {
		if (colIndices[i] != colIndices[i + 1]) {
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
				newPath.addPoint(colPoints[internalPoints[i]]);
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
				newPath.addPoint(colPoints[internalPoints[i]]);
				newPath.addIndex(internalPoints[i]);
			}
		}
	}
	updateMesh(newPath, internalFirst);
}

void Mesh::updateMesh(CollisionPath& path, bool internalFirst)
{
	MeshCutter cutter(&path, &vertices, &indices, internalFirst);
	cutter.cut();

	numberOfVertices = static_cast<unsigned int>(vertices.size());
	numberOfIndices = static_cast<unsigned int>(indices.size());
	numberOfBytes = numberOfBytes * sizeof(Vertex);
}
