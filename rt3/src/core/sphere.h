#ifndef SPHERE_H
#define SPHERE_H 1

#include "rt3.h"
#include "ray.h"
#include "material.h"
#include "primitive.h"
#include "math.h"

namespace rt3
{
    class Sphere : public Primitive
    {
    public:
        Point3f center;
        float radius;

        Sphere(const Point3f &center, float radius, Material *mat)
            : Primitive(mat), center(center), radius(radius) {}

        virtual ~Sphere(){};

        bool intersect_p(const Ray &r) const
        {
            Vector3f oc = Vector3f{1, 1, 1} * (r.o - center);
            auto a = r.d.dot(r.d);
            auto b = 2.0 * oc.dot(r.d);
            auto c = oc.dot(oc) - radius * radius;
            auto discriminant = b * b - 4 * a * c;
            return (discriminant > 0);
        }

        Vector3f normalAt(const Ray &ray, const Vector3f &intersection_point) const
        {
            Vector3f normal = intersection_point - center;
            normal.norm();
            return normal;
        }

        float hit_sphere(const Ray &r)
        {
            Vector3f oc = Vector3f{1, 1, 1} * (r.o - center);
            auto a = r.d.dot(r.d);
            auto b = 2.0 * oc.dot(r.d);
            auto c = oc.dot(oc) - radius * radius;
            auto discriminant = b * b - 4 * a * c;
            if (discriminant < 0)
            {
                return -1.0;
            }
            else
            {
                return (-b - sqrt(discriminant)) / (2.0 * a);
            }
        }

        ColorXYZ ray_color(const Ray &r)
        {
            float t = hit_sphere(r);
            float half = 0.5;
            Vector3f N = ((r.vector_at_parameter(t)) - Vector3f(0, 0, -1)).unit_vector();
            return ColorXYZ{((N[0] * 255)), ((N[1] * 255)) , ((N[2] * 255))};
        }
    };

}
#endif // SPHERE_H