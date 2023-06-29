#ifndef SPHERE_H
#define SPHERE_H 1

#include "rt3.h"
#include "ray.h"
#include "material.h"
#include "primitive.h"
#include "math.h"
#include "surfaceinteraction.h"

namespace rt3
{
    class Sphere : public Primitive
    {
    public:
        Point3f center;
        float radius;
        float eps = 0.001;

        Sphere(const Point3f &center, float radius, Material *mat)
            : Primitive(mat), center(center), radius(radius) {}

        virtual ~Sphere(){};

        bool intersect_p(const Ray &r) const
        {
            Vector3f oc = (oc.ToVector3(r.o) - center);
            auto a = r.d.dot(r.d);
            auto b = 2.0 * r.d.dot(oc) ;
            auto c = oc.dot(oc) - (radius * radius);
            auto discriminant = b * b - 4 * a * c;
            return (discriminant > 0);
        }

        bool intersect(const Ray &r,
                       SurfaceInteraction *surface)
            const
        {

            Point3f origin = r.o;
            Vector3f direction = r.d;

            Vector3f oc = (r.d.ToVector3(r.o) - center);
            auto a = r.d.dot(r.d);
            auto b = 2.0 * r.d.dot(oc);
            auto c = oc.dot(oc) - (radius * radius);

            float delta = (b * b) - (4.0 * a * c);

            if (delta < 0.0)
                return false;

            float r1 = (-b + sqrt(delta)) / (2 * a);
            float r2 = (-b - sqrt(delta)) / (2 * a);

            if (r1 > r2)
                std::swap(r1, r2);

            auto tHit = -r1;

            if (tHit > r.t_max || tHit < 0)
                return false;

            if (surface != nullptr)
            {
                surface->t = tHit;
                surface->p = r.point_at_parameter(surface->t);
                surface->m = material;

                surface->n = oc.ToVector3((surface->p - center) * 2.0).unit_vector();
                surface->wo = (-1.0 * (direction - origin)).unit_vector();

                surface->p = surface->p + (eps * surface->n);
            }

            return true;
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
            auto a = (r.d).length_squared();
            auto b = 2.0 * r.d.dot(oc);
            auto half_b = r.d.dot(oc);
            auto c = oc.length_squared() - radius * radius;
            auto discriminant = half_b * half_b - a * c;

            if (discriminant < 0)
            {
                return Vector3f{0, 0, 0};
            }
            else
            {
                return r.vector_at_parameter((-half_b - sqrt(discriminant)) / a);
            }

            // auto a = r.d.dot(r.d);
            // auto b = 2.0 * r.d.dot(oc);

            // auto c = oc.dot(oc) - (radius * radius);
            // auto discriminant = (b * b) - (4 * a * c);
            // if (discriminant < 0)
            // {
            //     return Vector3f{0, 0, 0};
            // }
            // else
            // {
            //     float t1 = (-b - sqrt(discriminant)) / (2.0 * a);
            //     float t2 = (-b + sqrt(discriminant)) / (2.0 * a);
            //     if (t1 > t2)
            //         std::swap(t1, t2);
            //     return r.vector_at_parameter(t1);
            // }
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