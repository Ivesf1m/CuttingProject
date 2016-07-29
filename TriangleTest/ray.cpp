#include "ray.h"
#include <iostream>

Ray::Ray(vec3& origin, vec3& direction)
{
    this->origin = origin;
    this->direction = normalize(direction);
}

vec3& Ray::getDirection()
{
    return direction;
}

void Ray::getPointAtLambda(float lambda, vec3 &point)
{
    point = origin + lambda * direction;
}

float Ray::getLambdaAtPoint(const vec3& point)
{
    vec3 aux = point - origin;
    vec3 zero(0.0f, 0.0f, 0.0f);
    if(cross(aux, direction) != zero)
        return -1; //point is not in this line.

    if(aux.x != 0.0f && direction.x != 0.0f)
        return aux.x / direction.x;
    else if(aux.y != 0.0f && direction.y != 0.0f)
        return aux.y / direction.y;
    else if(aux.z != 0.0f && direction.z != 0.0f)
        return aux.z / direction.z;
    else
        return 0.0f;
}

vec3& Ray::getOrigin()
{
    return origin;
}

void Ray::setDirection(vec3 &direction)
{
    this->direction = direction;
}

void Ray::setOrigin(vec3 &origin)
{
    this->origin = origin;
}

void Ray::printRayInfo()
{
    std::cout << "Ray origin: ";
    std::cout << origin.x << "\t" << origin.y << "\t" << origin.z << std::endl;

    std::cout << "Ray direction: ";
    std::cout << direction.x << "\t" << direction.y << "\t" << direction.z << std::endl;
}
