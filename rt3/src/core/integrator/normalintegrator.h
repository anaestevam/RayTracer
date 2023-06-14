#ifndef NORMAL_INTEGRATOR_H
#define NORMAL_INTEGRATOR_H

#include "integrator.h"
#include "../camera.h"
#include "../sphere.h"
#include "../rt3.h"

namespace rt3
{
class NormalIntegrator : public Integrator {
public:
    virtual ~NormalIntegrator() {}
    NormalIntegrator(Camera* cam) : Integrator(cam) {}
    virtual ColorXYZ Li(const Ray& ray, const Scene& scene,const Point2f &pixel_coords);
    virtual void render(const Scene& scene) override;

};
    NormalIntegrator *create_normal_integrator(const ParamSet &ps, Camera* cam );
    ColorXYZ RGBfromNormal(const Vector3f &normal);

}

#endif