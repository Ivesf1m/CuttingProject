#ifndef RAY_H
#define RAY_H

#include <glm.hpp>

using glm::vec3;

class Ray
{
public:
    Ray(vec3& origin, vec3& direction);

    vec3& getOrigin();
    vec3& getDirection();
    void setOrigin(vec3& origin);
    void setDirection(vec3& direction);
    void getPointAtLambda(float lambda, vec3& point);
    float getLambdaAtPoint(const vec3& point);
    void printRayInfo();

private:
    vec3 origin;
    vec3 direction;
};

#endif // RAY_H
