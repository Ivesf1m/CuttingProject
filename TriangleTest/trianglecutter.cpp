#include "trianglecutter.h"
#include <iostream>

#define COMP_ERROR 1e-5

TriangleCutter::TriangleCutter(unsigned int triangleIndex, const Triangle& t,
                               const vec3& entrancePoint, const vec3& internalPoint,
                               const vec3& exitPoint)
               : triangleIndex(triangleIndex), triangle(t), entrancePoint(entrancePoint),
                 internalPoint(internalPoint), exitPoint(exitPoint)

{
    //Setting up edges
    //Triangle vertices
    vec3 v1 = triangle.getVertex(0);
    vec3 v2 = triangle.getVertex(1);
    vec3 v3 = triangle.getVertex(2);

    //Directions
    vec3 d1, d2, d3;
    triangle.getEdge(0, 1, d1);
    triangle.getEdge(1, 2, d2);
    triangle.getEdge(2, 0, d3);

    //Constructing edges
    edge1 = new Ray(v1, d1);
    edge2 = new Ray(v2, d2);
    edge3 = new Ray(v3, d3);
}

TriangleCutter::~TriangleCutter()
{
    delete edge1;
    delete edge2;
    delete edge3;
}

bool TriangleCutter::compareWithError(vec3& v1, vec3& v2)
{
    vec3 aux = v2 - v1;
    if(fabs(aux.x) <= COMP_ERROR && fabs(aux.y) <= COMP_ERROR && fabs(aux.z) <= COMP_ERROR)
        return true;
    return false;
}

void TriangleCutter::cut()
{
    //First step: identify if entrance point and/or exit point coincide with vertices.
    //If they happen to be the same, the triangle will not be cut.

    if(entrancePoint == exitPoint)
        return;

    entranceIsVertex = isVertex(this->entrancePoint);
    exitIsVertex = isVertex(this->exitPoint);

    //First cut case: both the entrance and exit vertices are vertices of the triangle
    if(entranceIsVertex && exitIsVertex){
        cout << "Os dois sao vertices" << endl;
        cutEntranceAndExitVertices();
        return;
    }

    //Second cut case: either the entrance or the exit vertex is a triangle vertex
    if(entranceIsVertex){
        cout << "Apenas a entrada e' vertice" << endl;
        cutEntranceVertex();
        return;
    }

    if(exitIsVertex){
        cout << "Apenas a saida e' vertice" << endl;
        cutExitVertex();
        return;
    }

    //If entrance and exit points are not triangle vertices, we need to find out
    //to which edge they belong. They must belong to any of the edges, otherwise
    //an error must be returned. We also use this step to register which of the
    //triangle vertices is not on the same edge, since this info will be used
    //when subdividing the triangle.
    getPointsEdge(entrancePoint, &entranceEdge, &oppositeToEntrance);
    getPointsEdge(exitPoint, &exitEdge, &oppositeToExit);


    //Now that we know the edges, we have two more cut cases:
    //Third case: entrance and exit points are on the same edge
    if(entranceEdge == exitEdge){
        cout << "Entrance and exit on the same edge, but not vertices" << endl;
        cutSameEdge();
        return;
    }


    //Fourth case: entrance and exit points are on different edges.
    cout << "Entrance and exit on different edges and are not vertices" << endl;
    cutDifferentEdges();

}

void TriangleCutter::cutDifferentEdges()
{
    //First step: find which vertex is shared by the entrance and exit
    //edges
    const vec3* v1 = &(triangle.getVertex(0));
    const vec3* v2 = &(triangle.getVertex(1));
    const vec3* v3 = &(triangle.getVertex(2));
    const vec3* sharedVertex;

    if(oppositeToEntrance != v1 && oppositeToExit != v1)
        sharedVertex = v1;
    else if(oppositeToEntrance != v2 && oppositeToExit != v2)
        sharedVertex = v2;
    else
        sharedVertex = v3;

    //We can now subdivide the triangle in 5 new ones.
    Triangle t1(entrancePoint, internalPoint, *sharedVertex);
    Triangle t2(entrancePoint, *oppositeToExit, internalPoint);
    Triangle t3(exitPoint, internalPoint, *sharedVertex);
    Triangle t4(exitPoint, *oppositeToEntrance, internalPoint);
    Triangle t5(internalPoint, *oppositeToEntrance, *oppositeToExit);

    newTriangles.push_back(t1);
    newTriangles.push_back(t2);
    newTriangles.push_back(t3);
    newTriangles.push_back(t4);
    newTriangles.push_back(t5);
}

void TriangleCutter::cutEntranceAndExitVertices()
{
    //Both the entrance and the exit vertices are also vertices of the triangle.
    //First step is to find out which of the vertices of the triangle is not one
    //of these two.
    //Getting triangle vertices' pointers.
    const vec3* v1 = &(triangle.getVertex(0));
    const vec3* v2 = &(triangle.getVertex(1));
    const vec3* v3 = &(triangle.getVertex(2));
    const vec3* thirdVertex;

    if(entranceIsVertex != v1 && exitIsVertex != v1)
        thirdVertex = v1;
    else if(entranceIsVertex != v2 && exitIsVertex != v2)
        thirdVertex = v2;
    else
        thirdVertex = v3;

    //Three new triangles will be generated, as follows:
    Triangle t1(entrancePoint, internalPoint, exitPoint);
    Triangle t2(entrancePoint, internalPoint, *thirdVertex);
    Triangle t3(exitPoint, *thirdVertex, internalPoint);

    newTriangles.push_back(t1);
    newTriangles.push_back(t2);
    newTriangles.push_back(t3);
}

void TriangleCutter::cutEntranceVertex()
{

    //We need to identify which of the triangle's vertices is the entrance
    //Getting triangle vertices' pointers.
    const vec3* v1 = &(triangle.getVertex(0));
    const vec3* v2 = &(triangle.getVertex(1));
    const vec3* v3 = &(triangle.getVertex(2));
    const vec3 *secondVertex, *thirdVertex;

    if(entranceIsVertex == v1){
        secondVertex = v2;
        thirdVertex = v3;
    }else if(entranceIsVertex == v2){
        secondVertex = v3;
        thirdVertex = v1;
    }else{
        secondVertex = v1;
        thirdVertex = v3;
    }


    //In this case, the entrance vertex is one of the triangle's vertices.
    //Two cut cases can be generated. To identify them, we need to now if the
    //exit point is on the opposite edge to the entrance point or not.
    getPointsEdge(exitPoint, &exitEdge, &oppositeToExit);
    vec3 aux = glm::normalize(exitPoint - entrancePoint);
    vec3 zero(0.0f, 0.0f, 0.0f);

    //Doing the cross product of the edge's direction and a vector
    //from the entrance to the exit point. If this product is the
    //null vector, this means that entrance and exit share an edge.
    //Otherwise, exit is on the opposite edge.
    vec3 crossProduct = glm::cross(aux, exitEdge->getDirection());
    if(compareWithError(crossProduct, zero)){
        //this is the vertex of the triangle that is on the same edge of the
        //exit but is not the entrance
        const vec3* edgeVertex;
        if(oppositeToExit == secondVertex)
            edgeVertex = thirdVertex;
        else
            edgeVertex = secondVertex;

        //We now build 4 new triangles.
        Triangle t1(entrancePoint, internalPoint, exitPoint);
        Triangle t2(exitPoint, internalPoint, *edgeVertex);
        Triangle t3(entrancePoint, internalPoint, *oppositeToExit);
        Triangle t4(*edgeVertex, *oppositeToExit, internalPoint);

        newTriangles.push_back(t1);
        newTriangles.push_back(t2);
        newTriangles.push_back(t3);
        newTriangles.push_back(t4);
    }else{
        //Since the exitPoint is on the opposite edge, the triangle is divided in two others.
        Triangle t1(entrancePoint, exitPoint, *secondVertex);
        Triangle t2(entrancePoint, exitPoint, *thirdVertex);
        newTriangles.push_back(t1);
        newTriangles.push_back(t2);
    }
}

void TriangleCutter::cutExitVertex()
{
    //We need to identify which of the triangle's vertices is the exit
    //Getting triangle vertices' pointers.
    const vec3* v1 = &(triangle.getVertex(0));
    const vec3* v2 = &(triangle.getVertex(1));
    const vec3* v3 = &(triangle.getVertex(2));
    const vec3 *secondVertex, *thirdVertex;

    if(exitIsVertex == v1){
        secondVertex = v2;
        thirdVertex = v3;
    }else if(exitIsVertex == v2){
        secondVertex = v3;
        thirdVertex = v1;
    }else{
        secondVertex = v1;
        thirdVertex = v3;
    }

    //In this case, the exit vertex is one of the triangle's vertices.
    //Two cut cases can be generated. To identify them, we need to now if the
    //entrance point is on the opposite edge to the exit point or not.
    getPointsEdge(entrancePoint, &entranceEdge, &oppositeToEntrance);
    vec3 aux = exitPoint - entrancePoint;
    vec3 zero(0.0f, 0.0f, 0.0f);

    //Doing the cross product of the edge's direction and a vector
    //from the entrance to the exit point. If this product is the
    //null vector, this means that entrance and exit share an edge.
    //Otherwise, exit is on the opposite edge.
    vec3 crossProduct = glm::cross(aux, entranceEdge->getDirection());
    if(compareWithError(crossProduct, zero)){
        //this is the vertex of the triangle that is on the same edge of the
        //exit but is not the entrance
        const vec3* edgeVertex;
        if(oppositeToEntrance == secondVertex)
            edgeVertex = thirdVertex;
        else
            edgeVertex = secondVertex;

        //We now build 4 new triangles.
        Triangle t1(entrancePoint, internalPoint, exitPoint);
        Triangle t2(entrancePoint, internalPoint, *edgeVertex);
        Triangle t3(exitPoint, internalPoint, *oppositeToEntrance);
        Triangle t4(*edgeVertex, *oppositeToEntrance, internalPoint);

        newTriangles.push_back(t1);
        newTriangles.push_back(t2);
        newTriangles.push_back(t3);
        newTriangles.push_back(t4);
    }else{
        //Since the exitPoint is on the opposite edge, the triangle is divided in two others.
        Triangle t1(entrancePoint, exitPoint, *secondVertex);
        Triangle t2(entrancePoint, exitPoint, *thirdVertex);
        newTriangles.push_back(t1);
        newTriangles.push_back(t2);
    }

}

void TriangleCutter::cutSameEdge()
{
    //First we need to find which vertex of the edge is closer to the entrance
    //and which is closer to the exit
    const vec3 *v1, *v2; // vertices of the edge
    if(oppositeToEntrance == &(triangle.getVertex(0))){
        v1 = &(triangle.getVertex(1));
        v2 = &(triangle.getVertex(2));
    }else if(oppositeToEntrance == &(triangle.getVertex(1))){
        v1 = &(triangle.getVertex(2));
        v2 = &(triangle.getVertex(0));
    }else{
        v1 = &(triangle.getVertex(0));
        v2 = &(triangle.getVertex(1));
    }

    float d_v1, d_v2, d_exit; //distances
    d_v1 = glm::distance(entrancePoint, *v1);
    d_v2 = glm::distance(entrancePoint, *v2);
    vec3 closestToEntrance, closestToExit;
    if(d_v1 < d_v2){
        d_exit = glm::distance(exitPoint, *v1);
        if(d_exit < d_v1){
            closestToEntrance = *v2;
            closestToExit = *v1;
        }else{
            closestToEntrance = *v1;
            closestToExit = *v2;
        }
    }else{
        d_exit = glm::distance(exitPoint, *v2);
        if(d_exit < d_v2){
            closestToEntrance = *v1;
            closestToExit = *v2;
        }else{
            closestToEntrance = *v2;
            closestToExit = *v1;
        }
    }

    //We now break the triangle in 5 subtriangles

    //First triangle: entrance -> internal -> closest_entrance
    Triangle t1(entrancePoint, internalPoint, closestToEntrance);

    //Second triangle: exit -> internal -> closest_exit
    Triangle t2(exitPoint, internalPoint, closestToExit);

    //Third triangle: entrance -> internal -> exit
    Triangle t3(entrancePoint, internalPoint, exitPoint);

    //Fourth triangle: closest_entrance -> entrance_v3 -> internal
    Triangle t4(closestToEntrance, *oppositeToEntrance, internalPoint);

    //Fifth triangle: closest_exit -> entrance_v3 -> internal
    Triangle t5(closestToExit, *oppositeToEntrance, internalPoint);

    //The initial triangle will not exist anymore, it will be susbitituded in the triangle list
    //by t1. The other 4 triangles will be inserted in the back of the list.
    newTriangles.push_back(t1);
    newTriangles.push_back(t2);
    newTriangles.push_back(t3);
    newTriangles.push_back(t4);
    newTriangles.push_back(t5);
}

std::vector<Triangle>& TriangleCutter::getNewTriangles()
{
    return newTriangles;
}

void TriangleCutter::getPointsEdge(const vec3& point, Ray** edge, const vec3** oppositePoint)
{
    //We will be using the parametric equation of a ray to figure out
    //to which edge the point belongs to. It will be the edge that returns
    //a non-zero lambda.
    float lambda = 0.0f;

    //Testing the first edge
    lambda = edge1->getLambdaAtPoint(point);
    if(lambda != -1.0f){
        cout << "e' a edge1" << endl;
        *edge = edge1;
        //Edge 1 is delimited by vertices 0 and 1 of the triangle,
        //so oppositePoint is vertex 2.
        *oppositePoint = &(triangle.getVertex(2));
        return;
    }

    //Testing the second edge
    lambda = edge2->getLambdaAtPoint(point);
    if(lambda != -1.0f){
        cout << "e' a edge2" << endl;
        *edge = edge2;
        //Edge 2 is delimited by vertices 1 and 2 of the triangle,
        //so oppositePoint is vertex 0.
        *oppositePoint = &(triangle.getVertex(0));
        return;
    }

    //Third edge
    lambda = edge3->getLambdaAtPoint(point);
    if(lambda != -1.0f){
        cout << "e' a edge3" << endl;
        *edge = edge3;
        //Edge 3 is delimited by vertices 2 and 0 of the triangle,
        //so oppositePoint is vertex 1.
        *oppositePoint = &(triangle.getVertex(1));
        return;
    }

    //None of the 3 edges was a match, so there is an error.
    std::cerr << "O ponto de entrada ou de saída do corte não está contido em nenhuma das arestas." << std::endl;
    exit(1);
}

const vec3* TriangleCutter::isVertex(const vec3& point)
{
    if(point == triangle.getVertex(0))
        return &(triangle.getVertex(0));
    else if(point == triangle.getVertex(1))
        return &(triangle.getVertex(1));
    else if(point == triangle.getVertex(2))
        return &(triangle.getVertex(2));
    else return NULL;
}
