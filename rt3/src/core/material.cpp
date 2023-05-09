#include "material.h"

Material::Material() {}

Material::Material(const Vector3f &ambient, const Vector3f &diffuse, const Vector3f &specular, float shininess, float reflectivity)
    : _ambient(ambient), _diffuse(diffuse), _specular(specular), _shininess(shininess), _reflectivity(reflectivity) {}

Vector3f Material::ambient() const
{
    return _ambient;
}

Vector3f Material::diffuse() const
{
    return _diffuse;
}

Vector3f Material::specular() const
{
    return _specular;
}

float Material::shininess() const
{
    return _shininess;
}

float Material::reflectivity() const
{
    return _reflectivity;
}
