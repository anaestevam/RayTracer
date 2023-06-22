#include "directionalLight.h"

namespace rt3
{

DirectionalLight* create_directional_light(const ParamSet& ps)
{
    // Extract the necessary properties from the ParamSet
    Vector3f L = retrieve(ps, "L", Vector3f(1.0f, 1.0f, 1.0f));
    Vector3f scale = retrieve(ps, "scale", Vector3f(1.0f, 1.0f, 1.0f));
    Point3f from = retrieve(ps, "from", Point3f(0.0f, 0.0f, 0.0f));
    Point3f to = retrieve(ps, "to", Point3f(0.0f, 0.0f, -1.0f));

    // Create and return the DirectionalLight object
    return new DirectionalLight(L, scale, from, to);
}

} // namespace rt3