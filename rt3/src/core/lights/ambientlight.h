#ifndef AMBIENT_LIGHT
#define AMBIENT_LIGHT

#include "light.h"
#include "../rt3.h"
#include "../paramset.h"

namespace rt3
{
class AmbientLight : public Light {

public:
    Point3f direction; 

    AmbientLight ( Vector3f intensity )
        : Light{intensity} {}

    AmbientLight ()
        : Light{ Vector3f(0.1, 0.1, 0.1) }{}

    ~AmbientLight(){  }

    Vector3f Li(
        const SurfaceInteraction &isect,
        Vector3f *wi,
        VisibilityTester *vt) const;

    bool is_ambient(){ return true;} 

};
 AmbientLight* create_ambient_light(const ParamSet& ps);

} // namespace rt3

#endif