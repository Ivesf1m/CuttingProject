#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glm.hpp>
#include <mesh.h>

using glm::vec3;

class Triangle
{

public:
    Triangle(Mesh* mesh, unsigned int i1, unsigned int i2, unsigned int i3);
    Triangle(const vec3& v1, const vec3& v2, const vec3& v3);
    Triangle(const Triangle& t);

    const vec3& getVertex(unsigned int i);

    //Copia a direção da aresta formada pelos vértices
    //de índice v1 (origem) e v2 (ponto final) para edge.
    void getEdge(unsigned int v1, unsigned int v2, vec3& edge);

    const vec3& getNormal();
    const vec3* getVertices();

    //O vértice de índice index deste triângulo
    //recebe o do novo índice vertex_index.
    //Lembrar da restrição anti-horária!
    void setVertex(unsigned int index, unsigned int vertex_index);

    void printTriangleInfo();

private:
    //Vértices em sentido anti-horário
    vec3 verts[3];
    vec3 normal;
    Mesh* mesh;

};

#endif // TRIANGLE_H
