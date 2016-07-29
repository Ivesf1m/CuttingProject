#include "triangle.h"
#include "mesh.h"
#include <iostream>

Triangle::Triangle(Mesh* mesh, unsigned int i1, unsigned int i2, unsigned int i3)
         : mesh(mesh)
{
    verts[0] = mesh->getVertex(i1).position();
    verts[1] = mesh->getVertex(i2).position();
    verts[2] = mesh->getVertex(i3).position();

    normal = cross((verts[1] - verts[0]), (verts[2] - verts[1]));
    normal = normalize(normal);
}

Triangle::Triangle(const vec3& v1, const vec3& v2, const vec3& v3)
{
    verts[0] = v1;
    verts[1] = v2;
    verts[2] = v3;

    normal = cross((verts[1] - verts[0]), (verts[2] - verts[1]));
    normal = normalize(normal);
}

Triangle::Triangle(const Triangle& t)
{
    for(int i = 0; i < 3; ++i)
        this->verts[i] = t.verts[i];
    this->normal = t.normal;
}

void Triangle::getEdge(unsigned int v1, unsigned int v2, vec3 &edge)
{
    if((v1 > 2) || (v2 > 2)){
        std::cerr << "Erro: indices de vertices de triangulos devem ser valores entre 0 e 2." << std::endl;
        return;
    }
    edge = verts[v2] - verts[v1];
}

const vec3& Triangle::getNormal()
{
    return normal;
}

const vec3& Triangle::getVertex(unsigned int i)
{
    if(i > 2){
        std::cerr << "Erro: indices de vertices de triangulos devem ser valores entre 0 e 2." << std::endl;
        exit(1);
    }
    return verts[i];
}

 const vec3* Triangle::getVertices()
 {
     return verts;
 }

void Triangle::setVertex(unsigned int index, unsigned int vertex_index)
{
    if(index > 2){
        std::cerr << "Erro: indices de vertices de triangulos devem ser valores entre 0 e 2." << std::endl;
        exit(1);
    }
    verts[index] = mesh->getVertex(vertex_index).position();
}

void Triangle::printTriangleInfo()
{
    //std::cout << "Triangle info: " << std::endl;
    //std::cout << "First Vertex Index: " << verts[0] << std::endl;
    //std::cout << "Second Vertex Index: " << verts[1] << std::endl;
    //std::cout << "Third Vertex Index: " << verts[2] << std::endl;
}
