#include "ambientlight.h"

namespace rt3
{

AmbientLight* create_ambient_light(const ParamSet& ps)
{
    // Extract the necessary properties from the ParamSet
    Vector3f L = retrieve(ps, "L", Vector3f{0.2f, 0.2f, 0.2f});

    // Create and return the AmbientLight object
    // return new AmbientLight(
    //     retrieve(ps, "L", ColorXYZ{0,0,0})
    // //    retrieve(ps, "scale", Vector3f{0,0,0})
    // );
}

} // namespace rt3
