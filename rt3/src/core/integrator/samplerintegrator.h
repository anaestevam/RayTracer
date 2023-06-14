#ifndef SAMPLER_INTEGRATOR_H
#define SAMPLER_INTEGRATOR_H

#include "integrator.h"
#include "../camera.h"
#include "../sphere.h"
#include "../rt3.h"

namespace rt3
{
class SamplerIntegrator : public Integrator {
public:
    virtual ~SamplerIntegrator() {}
    SamplerIntegrator(Camera* cam) : Integrator(cam) {}
    virtual ColorXYZ Li(const Ray& ray, const Scene& scene,const Point2f &pixel_coords);
    virtual void render(const Scene& scene) override;

};
    SamplerIntegrator *create_sample_integrator(const ParamSet &ps, Camera* cam );

}

#endif