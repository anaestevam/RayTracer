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

        Vector3f hit_sphere(const Ray &r)
        {
            Vector3f oc = (r.d.ToVector3(r.o) - center);

            auto a = r.d.dot(r.d);
            auto b = 2.0 * r.d.dot(oc);

            auto c = oc.dot(oc) - (radius * radius);
            auto discriminant = (b * b) - (4 * a * c);
            if (discriminant < 0)
            {
                return Vector3f{0, 0, 0};
            }
            else
            {
                float t1 = (-b - sqrt(discriminant)) / (2.0 * a);
                float t2 = (-b + sqrt(discriminant)) / (2.0 * a);
                if (t1 > t2) std::swap(t1, t2);

                return r.vector_at_parameter(t1);
            }
        }

        ColorXYZ ray_color(const Ray &r)
        {
            Vector3f intersection_point = hit_sphere(r);
            if (intersection_point == Vector3f{0, 0, 0})
            {
                return ColorXYZ{0, 0, 0};
            }
            Vector3f normal = (intersection_point - center).normalized();
            return ColorXYZ{(std::abs(normal[0]) * 255) / 2, (std::abs(normal[1]) * 255) / 2, std::abs((normal[2]) * 255) / 2};
        }
    };

}
#endif // SPHERE_H