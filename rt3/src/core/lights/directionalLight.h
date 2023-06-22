#ifndef _DIRECTIONAL_LIGHT_
#define _DIRECTIONAL_LIGHT_

#include "light.h"
namespace rt3{
    
class DirectionalLight : public Light {

private:
    Point3f direction; 

public:

    DirectionalLight( 
        Point3f intensity,
        Point3f direction)
    : Light{intensity}, 
      direction{direction}
      {}
    
    Vector3f Li(
        const SurfaceInteraction &isect,
        Vector3f *wi,
        VisibilityTester *vt) const;

    Point3f get_direction(){ return direction; }

};
AmbientLight* create_ambient_light(const ParamSet& ps);

}
#endif