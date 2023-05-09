#ifndef MATERIAL_H
#define MATERIAL_H

#include "rt3.h"

class Material
{
public:
    Material();
    Material(const Vector3f &ambient, const Vector3f &diffuse,
             const Vector3f &specular, float shininess, float reflectivity);

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

#endif // MATERIAL_H
