#ifndef PRIMITIVE_H
#define PRIMITIVE_H 1

#include "rt3.h"
#include "ray.h"
#include "material.h"

namespace rt3
{
    class Primitive
    {
    public:
        // Add a constructor that takes a Primitive object as its argument
        explicit Primitive(const Primitive &other)
        {
            material = other.material;
        }

        // Add a constructor that takes a Material object as its argument
        explicit Primitive(Material *mat)
        {
            material = mat;
        }

        virtual ~Primitive(){};
        // Simpler & faster version of intersection that only return true/false.
        // It does not compute the hit point information.
        virtual bool intersect_p(const Ray &r) const
        {
            return 0;
        };

        Material *material;
    };

    Primitive *create_primitive(const ParamSet &ps, Material* material);
}
#endif // PRIMITIVE_H