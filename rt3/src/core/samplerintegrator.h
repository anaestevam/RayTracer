#ifndef SAMPLE_INTEGRATOR_H
#define SAMPLE_INTEGRATOR_H

#include "integrator.h"
#include "camera.h"
#include "sphere.h"
namespace rt3
{
class SamplerIntegrator : public Integrator {
public:
    virtual ~SamplerIntegrator() {}
    SamplerIntegrator(Camera* cam) : camera(cam) {}
    virtual ColorXYZ Li(const Ray& ray, const Scene& scene);
    virtual void render(const Scene& scene) override;
    SamplerIntegrator *create_sample_integrator(const ParamSet &ps, Camera* cam ) const;

private:
    Camera* camera;
};
}

#endif