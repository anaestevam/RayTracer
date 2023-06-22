#include "spotyLight.h"

namespace rt3 {

PointLight* create_point_light( const ParamSet &ps ){
    Point3f from = retrieve(ps, "from", Point3f());
    Point3f to = retrieve(ps, "to", Point3f());

    return new SpotyLight(
        retrieve(ps, "I", Color()),
        retrieve(ps, "scale", Vector3f()),
        from,
        (to - from).normalized(),
        retrieve(ps, "cutoff", real_type()),
        retrieve(ps, "falloff", real_type())
    );
}
}