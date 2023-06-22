#ifndef _SPOTY_LIGHT_H
#define _SPOTY_LIGHT_H

#include "light.h"
namespace rt3 {
    
class SpotyLight : public Light {

private:

Point3f position;
Point3f point_at;
int cutoff;
int falloff;

public:

    SpotyLight ( 
        point3 intensity,
        point3 position,
        point3 point_at,
        int cutoff,
        int falloff
    ) : Light{intensity},
        position{position},
        point_at{point_at},
        cutoff{cutoff},
        falloff{falloff} {}

    ~SpotyLight (){ /*empty*/ }

    point3 get_position () { return position; }

    point3 get_point_at () { return point_at; }

    int get_cutoff () { return cutoff; }

    int get_falloff () { return falloff; }

    Vec3 Li(
        const SurfaceInteraction &isect,
        vector *wi,
        VisibilityTester *vt) const;

};
    PointLight* create_point_light(const ParamSet& ps);
}
#endif