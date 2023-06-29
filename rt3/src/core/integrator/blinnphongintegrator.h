#ifndef BLINNPHONG_INTEGRATOR_H
#define BLINNPHONG_INTEGRATOR_H

#include "integrator.h"
#include "../camera.h"
#include "../sphere.h"
#include "../rt3.h"
#include "../visibilitytester.h"

namespace rt3
{
class BlinnPhongIntegrator : public Integrator {
public:

    Bounds3 bounding_box_world;

    virtual ~BlinnPhongIntegrator() {}
    BlinnPhongIntegrator(Camera* cam) : Integrator(cam) {}
    virtual ColorXYZ Li(const Ray& ray, const Scene& scene,const Point2f &pixel_coords);
    virtual void render(const Scene& scene) override;

};
    BlinnPhongIntegrator *create_blinnphong_integrator(const ParamSet &ps, Camera* cam );

}

#endif