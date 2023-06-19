#include "ambientlight.h"

namespace rt3
{

AmbientLight* create_ambient_light(const ParamSet& ps)
{
    // Extract the necessary properties from the ParamSet
    Vector3f L = retrieve(ps, "L", Vector3f{0.2f, 0.2f, 0.2f});

    // Create and return the AmbientLight object
    return new AmbientLight(L);
}

// DirectionalLight* create_directional_light(const ParamSet& ps)
// {
//     // Extract the necessary properties from the ParamSet
//     Vector3f L = retrieve(ps, "L", Vector3f(1.0f, 1.0f, 1.0f));
//     Vector3f scale = retrieve(ps, "scale", Vector3f(1.0f, 1.0f, 1.0f));
//     Vector3f from = retrieve(ps, "from", Vector3f(0.0f, 0.0f, 0.0f));
//     Vector3f to = retrieve(ps, "to", Vector3f(0.0f, 0.0f, -1.0f));

//     // Create and return the DirectionalLight object
//     return new DirectionalLight(L, scale, from, to);
// }



Vector3f AmbientLight::Li(
    const SurfaceInteraction &isect,
    Vector3f *wi,
    VisibilityTester *vt) const
{
   
    UNUSED(isect);
    UNUSED(wi);
    UNUSED(vt);

    return intensity;
}

} // namespace rt3
