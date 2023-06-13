#ifndef MATERIAL_H
#define MATERIAL_H

#include "rt3.h"
#include "paramset.h"
#include "light.h"

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
        // virtual ColorXYZ emitted(const Ray &ray, const Surfel &surfel, const Vector3f &dir) const = 0;
    };
    Material *create_material(const ParamSet &ps);


    class FlatMaterial : public Material
    {
    public:
        FlatMaterial(const ColorXYZ &color, float reflectivity, float transparency)
            : Material(color, reflectivity, transparency) {}
        // ColorXYZ emitted(const Ray &ray, const Surfel &surfel, const Vector3f &dir) const override
        // {
        //     return color;
        // }
    };

    class FrostedGlassMaterial : public Material
    {
    public:
        FrostedGlassMaterial(const ColorXYZ &color, float reflectivity, float transparency, float roughness, float opacity)
            : Material(color, reflectivity, transparency), roughness(roughness), opacity(opacity) {}

        float roughness;
        float opacity;
        //         ColorXYZ emitted(const Ray &ray, const Surfel &surfel, const Vector3f &dir) const override
        // {
        //     // Implement the emitted light calculation for the diffuse material.
        //     // This is just an example; you may need to adjust the code to fit your specific requirements.
        //     float cos_theta = dir.dot(ray.d);
        //     if (cos_theta < 0.0f)
        //     {
        //         return ColorXYZ{0, 0, 0};
        //     }
        //     float emitted_color = cos_theta;
        //     return ColorXYZ{0, 0, 0};
        //}
    };

    // class BlinnMaterial : public Material
    // {
    // public:
    //     BlinnMaterial(const Vector3f &ambient, const Vector3f &kd, const Vector3f &ks, float glossiness)
    //         : Material(ColorXYZ{0, 0, 0}, 0, 0), ambient(ambient), diffuse(diffuse), specular(specular), glossiness(glossiness) {}

    //     Vector3f ambient;
    //     Vector3f diffuse;
    //     Vector3f specular;
    //     float glossiness;
    //     ColorXYZ emitted(const Ray &ray, const Surfel &surfel, const Vector3f &dir) const override
    //     {
    //         // Implement the emitted light calculation for the diffuse material.
    //         // This is just an example; you may need to adjust the code to fit your specific requirements.
    //         float cos_theta = dir.dot(ray.d);
    //         if (cos_theta < 0.0f)
    //         {
    //             return ColorXYZ{0, 0, 0};
    //         }
    //         float emitted_color = ambient.dot(ambient) * cos_theta;
    //         return ColorXYZ{0, 0, 0};
    //     }
    // };
}

#endif // MATERIAL_H
