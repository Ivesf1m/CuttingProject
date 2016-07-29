#ifndef TRIANGLECUTTER_H
#define TRIANGLECUTTER_H

#include "triangle.h"
#include "ray.h"
#include <vector>

class TriangleCutter
{
    public:
        TriangleCutter(unsigned int triangleIndex, const Triangle& t,
                       const vec3& entrancePoint, const vec3& internalPoint,
                       const vec3& exitPoint);

        ~TriangleCutter();

        void cut();
        std::vector<Triangle>& getNewTriangles();

    private:
        unsigned int triangleIndex;
        Triangle triangle;
        vec3 entrancePoint;
        vec3 internalPoint;
        vec3 exitPoint;
        Ray* edge1;
        Ray* edge2;
        Ray* edge3;
        Ray* entranceEdge;
        Ray* exitEdge;
        const vec3* entranceIsVertex;
        const vec3* exitIsVertex;
        const vec3* oppositeToEntrance;
        const vec3* oppositeToExit;
        std::vector<Triangle> newTriangles;


        //Helper functions
        const vec3* isVertex(const vec3& point);
        void getPointsEdge(const vec3& point, Ray** edge, const vec3** oppositePoint);
        bool compareWithError(vec3& v1, vec3& v2);

        //Cutting functions
        void cutDifferentEdges();
        void cutEntranceAndExitVertices();
        void cutEntranceVertex();
        void cutExitVertex();
        void cutSameEdge();
};

#endif // TRIANGLECUTTER_H
