#ifndef SPHERE_H
#define SPHERE_H 1

#include "rt3.h"
#include "ray.h"
#include "material.h"
#include "primitive.h"

namespace rt3
{
    class Sphere : public Primitive
    {
    public:
        Point3f center;
        float radius;

        Sphere(const Point3f &center, float radius) : center(center), radius(radius) {}
        virtual ~Sphere(){};

        bool intersect_p(const Ray &ray) const
        {
            // Point3f m = center - ray.o;
            // TO-DO multipllicar
            //  float b = m.Dot(ray.d);
            //  float c = m.Dot(m) - radius * radius;

            // if (b < 0 && c > 0)
            // {
            //     return false;
            // }
            // float discr = b * b - c;
            return 0;
        }
        const Material *get_material(void) const
        {
            return new Material();
        }
    };
}
#endif // SPHERE_H