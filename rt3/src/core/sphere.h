#ifndef SPHERE_H
#define SPHERE_H 1

#include "rt3.h"
#include "ray.h"
#include "material.h"
#include "primitive.h"

namespace rt3 {
    class Sphere : public Primitive {
    public:
        Point3f center;
        float radius;

        Sphere(const Point3f &center, float radius, Material *mat)
            : Primitive(mat), center(center), radius(radius) {}

        virtual ~Sphere(){};

        bool intersect_p(const Ray &r) const {
            Vector3f oc = Vector3f{1,1,1} * (r.o - center);
            auto a = r.d.dot(r.d);
            auto b = 2.0 * oc.dot(r.d);
            auto c = oc.dot(oc) - radius*radius;
            auto discriminant = b*b - 4*a*c;
            return (discriminant > 0);
        }               

    };
}
#endif // SPHERE_H