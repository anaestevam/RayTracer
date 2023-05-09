#ifndef CAMERA_H
#define CAMERA_H 1

#include "ray.h"

class Camera
{
    virtual Ray generate_ray(int x, int y) = 0;
};
class PerspectiveCamera : public Camera
{
    // ...
};
class OrthographicCamera : public Camera
{
    // ...
};
#endif // CAMERA_H
