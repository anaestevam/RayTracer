#ifndef MATERIAL_H
#define MATERIAL_H

#include "rt3.h"
#include "paramset.h"
namespace rt3
{
    class Material
    {
    public:
        Material(const ColorXYZ &color, float reflectivity, float transparency)
            : color(color), reflectivity(reflectivity), transparency(transparency) {}

        ColorXYZ color;
        float reflectivity;
        float transparency;
    };
    Material *create_material(const ParamSet &ps);

    class FrostedGlassMaterial : public Material {
        public:
            FrostedGlassMaterial(const ColorXYZ &color, float reflectivity, float transparency, float roughness, float opacity)
                : Material(color, reflectivity, transparency), roughness(roughness), opacity(opacity) {}

            float roughness;
            float opacity;
    };  
}

#endif // MATERIAL_H


