#ifndef PRIMITIVE_H
#define PRIMITIVE_H 1

#include "rt3.h"
#include "ray.h"
#include "material.h"

class SurfaceInteraction;

namespace rt3
{
    class Primitive
    {
    public:
        explicit Primitive(const Primitive &other)
        {
            material = other.material;
        }

        explicit Primitive(Material *mat)
        {
            material = mat;
        }

        virtual ~Primitive(){};

        virtual bool intersect(const Ray &r, SurfaceInteraction *surface) const
        {
            return 0;
        };

        virtual bool intersect_p(const Ray &r) const
        {
            return 0;
        };

        virtual Vector3f intersect_p_vector(const Ray &r) const
        {
            return Vector3f{0, 0, 0};
        };

        Material *material;
    };

    std::unique_ptr<rt3::Primitive> create_primitive(const ParamSet &ps, rt3::Material *material);
    Sphere create_sphere(const ParamSet &ps, rt3::Material *material);

}
#endif // PRIMITIVE_H