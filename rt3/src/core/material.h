#ifndef MATERIAL_H
#define MATERIAL_H

#include "rt3.h"
#include "paramset.h"
namespace rt3
{
    class Material
    {
    public:
        Material() {}

        Material(const Vector3f &ambient, const Vector3f &diffuse, const Vector3f &specular, float shininess, float reflectivity)
            : _ambient(ambient), _diffuse(diffuse), _specular(specular), _shininess(shininess), _reflectivity(reflectivity) {}

        Vector3f ambient() const;
        Vector3f diffuse() const;
        Vector3f specular() const;
        float shininess() const;
        float reflectivity() const;

    private:
        Vector3f _ambient;
        Vector3f _diffuse;
        Vector3f _specular;
        float _shininess;
        float _reflectivity;
    };
    Material *create_material(const ParamSet &ps);
}
#endif // MATERIAL_H
