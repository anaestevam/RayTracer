#include "primitive.h"
#include "rt3.h"
#include "paramset.h"
#include "ray.h"
#include "sphere.h"

namespace rt3
{

Primitive *create_primitive(const ParamSet &ps)
{
    // Extract the required parameters from the ParamSet object
    std::string type = retrieve(ps, "type", std::string{""});

    // Create a Primitive object based on the type
    Material *default_material = new FrostedGlassMaterial(ColorXYZ{1, 1, 1}, 0.5, 0.5, 0.1, 0.8); // You may need to provide a default material here
    Primitive *primitive = new Sphere(Point3f{0, 0, 0}, 3, default_material);
    if (type == "sphere")
    {
        float radius = retrieve(ps, "radius", float{0.0});
        Point3f center = retrieve(ps, "center", Point3f{0, 0, 0});
        // Assuming you have the material extracted from the ParamSet as well
        // Material *material = retrieve(ps, "material", default_material);
        primitive = new Sphere(center, radius, default_material);
    }
    else
    {
        // Handle other primitive types or throw an exception if the type is not supported
    }

    return primitive;
}

}