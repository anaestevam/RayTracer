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
    Primitive *primitive = new Sphere(Point3f{0, 0, 0}, 3);
    if (type == "sphere")
    {
      float radius = retrieve(ps, "radius", float{0.0});
      Point3f center = retrieve(ps, "center", Point3f{{0, 0, 0}});
      primitive = new Sphere(center, radius);
    }
    else
    {
      // Handle other primitive types or throw an exception if the type is not supported
    }

    return primitive;
  }
}