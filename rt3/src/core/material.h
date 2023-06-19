#ifndef MATERIAL_H
#define MATERIAL_H

#include "rt3.h"
#include "paramset.h"
#include "./lights/light.h"

namespace rt3
{
    class Material
    {
    public:
        Material(const ColorXYZ &color, float reflectivity, float transparency)
            : color(color), reflectivity(reflectivity), transparency(transparency) {}

        Material(const Material &m)
            : color(m.color), reflectivity(m.reflectivity), transparency(m.reflectivity) {}

        virtual ~Material() = default;
        virtual void someFunction() = 0;
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
        void someFunction() override
        {
            // Implementation of the virtual function
        }
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
        // }
        void someFunction() override
        {
            // Implementation of the virtual function
        }
    };

    class BlinnMaterial : public Material
    {

    private:
        Point3f ka;
        Point3f kd;
        Point3f ks;
        int ge;

    public:
        BlinnMaterial(const ColorXYZ &color, float reflectivity, float transparency,
                      Point3f ka,
                      Point3f kd,
                      Point3f ks,
                      int ge) : Material(color, reflectivity, transparency),
                                ka{ka}, kd{kd}, ks{ks}, ge{ge} {}

        // BlinnMaterial(const ColorXYZ &color, float reflectivity, float transparency) : Material(color, reflectivity, transparency),
        //                                          ka(0.1, 0.1, 0.1), kd(0.9, 0.2, 0.1), ks(0.8, 0.8, 0.1), ge(64) {}

        ~BlinnMaterial() {}

        Point3f get_ka() { return this->ka; }

        Point3f get_kd() { return this->kd; }

        Point3f get_ks() { return this->ks; }

        int get_ge() { return this->ge; }

        void someFunction() override
        {
            // Implementation of the virtual function
        }
    };

}

#endif // MATERIAL_H
