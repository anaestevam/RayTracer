#include "primitive.h"
#include "rt3.h"
#include "paramset.h"
#include "ray.h"
#include "sphere.h"

namespace rt3
{

std::unique_ptr<rt3::Primitive> create_primitive(const ParamSet& ps, rt3::Material *material)
{
    // Extract the required parameters from the ParamSet object
    std::string type = retrieve(ps, "type", std::string{""});

    // Create a Primitive object based on the type
    std::unique_ptr<rt3::Primitive> primitive;

    if (type == "sphere")
    {
        float radius = retrieve(ps, "radius", float{0.0});
        Point3f center = retrieve(ps, "center", Point3f{0, 0, 0});
        primitive = std::make_unique<rt3::Sphere>(center, radius, std::move(material));
    }
    else
    {
        // Handle other primitive types or throw an exception if the type is not supported
        // For example:
        throw std::runtime_error("Unsupported primitive type: " + type);
    }

    return primitive;
}

Sphere create_sphere(const ParamSet& ps, rt3::Material *material)
{
    std::string type = retrieve(ps, "type", std::string{""});

    if (type == "sphere")
    {
        float radius = retrieve(ps, "radius", float{0.0});
        Point3f center = retrieve(ps, "center", Point3f{0, 0, 0});
        return Sphere(center, radius, std::move(material));
    }
}
}