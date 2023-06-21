#ifndef _DIRECTIONAL_LIGHT_
#define _DIRECTIONAL_LIGHT_

#include "light.h"

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

#endif