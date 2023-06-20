#ifndef MATERIAL_H
#define MATERIAL_H

#include "rt3.h"
#include "paramset.h"
#include "ray.h"
#include "surfaceinteraction.h"
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
        virtual bool emitted(const Ray &ray, const SurfaceInteraction &surfel, ColorXYZ& attenuation, Ray& scattered) const = 0;
    };
    Material *create_material(const ParamSet &ps);

    class FlatMaterial : public Material
    {
    public:
        FlatMaterial(const ColorXYZ &color, float reflectivity, float transparency)
            : Material(color, reflectivity, transparency) {}
        bool emitted(const Ray &ray, const SurfaceInteraction &surfel,ColorXYZ& attenuation, Ray& scattered) const override
        {
            Vector3f scatter_direction = scatter_direction.ToVector3(surfel.p.normalized()) + scatter_direction.random_unit_vector();

            if (scatter_direction.near_zero())
                scatter_direction = scatter_direction.ToVector3(surfel.p.normalized());

            scattered = Ray(surfel.p, scatter_direction);
            attenuation = color;
            return true;
    
        }
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

        bool emitted(const Ray &ray, const SurfaceInteraction &surfel, ColorXYZ& attenuation, Ray& scattered) const override
        {
            Vector3f recordNormal = recordNormal.ToVector3(surfel.p.normalized());
            Vector3f reflected = reflect(ray.d.unit_vector(), recordNormal);
            scattered = Ray(surfel.p, reflected);
            attenuation = color;
            return (scattered.d.dot(recordNormal) > 0);
            
        }

        inline Vector3f reflect(const Vector3f& v, const Vector3f& n) const{
            return v - 2*v.dot(n)*n;
        }

        void someFunction() override
        {
            // Implementation of the virtual function
        }
    };

}

#endif // MATERIAL_H
