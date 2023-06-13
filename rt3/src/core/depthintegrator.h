#ifndef DEPTH_INTEGRATOR_H
#define DEPTH_INTEGRATOR_H

#include "integrator.h"
#include "camera.h"
#include "rt3.h"
#include "sphere.h"

namespace rt3
{
    class DepthIntegrator : public Integrator {
    public:
        virtual ~DepthIntegrator() {}
        DepthIntegrator(Camera* cam, float zmin, float zmax, ColorXYZ near_color, ColorXYZ far_color) : Integrator(cam), zmin(zmin), zmax(zmax), near_color(near_color), far_color(far_color) {}
        virtual ColorXYZ Li(const Ray& ray, const Scene& scene,const Point2f &pixel_coords);
        virtual void render(const Scene& scene) override;
        // virtual void preprocess(const Scene& scene) override;

    private:
        ColorXYZ near_color;
        ColorXYZ far_color;
        float zmin;
        float zmax;
    std::vector<float> m_z_buffer;
    };

    DepthIntegrator* create_depth_integrator(const ParamSet& ps, Camera* cam);
    float calculate_normalized_depth(const Ray &ray, const Scene &scene, const Point2f &pixel_coords, float min_z , float max_z);
    float sphere_distance(const Point3f &point, const Point3f &center, float radius);
    ColorXYZ interpolate(int color1, int color2, float fraction);
}

#endif // DEPTH_INTEGRATOR_H
