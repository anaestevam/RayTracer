#ifndef LIGHT_H
#define LIGHT_H

#include "../rt3.h"
#include "../bounds3.h"
#include "../common.h"

namespace rt3
{
class VisibilityTester;
class SurfaceInteraction;

class Light { 

protected:

    Vector3f intensity; 
    Bounds3 bounding_box_world;

public:

    Light( Vector3f intensity ) :
        intensity{intensity} {}

    Light() : intensity{ Vector3f(0.1, 0.1, 0.1)}{}

    virtual ~Light(){  }

    virtual Vector3f Li(
        const SurfaceInteraction &isect,
        Vector3f *wi,
        VisibilityTester *vt) const
        { UNUSED(isect); UNUSED(wi); UNUSED(vt); return Vector3f(0, 0, 0); }     

    virtual bool is_ambient(){ return false;} 

    Point3f get_intensity(){ return this->intensity.ToPoint3(); }

    void set_bounding_box( const Bounds3 & b )
    { this->bounding_box_world = b; }

};

} // namespace rt3

#endif