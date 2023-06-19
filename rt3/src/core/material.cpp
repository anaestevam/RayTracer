#include "material.h"
#include "rt3.h"
#include "paramset.h"
#include "ray.h"

namespace rt3
{

    Material *create_material(const ParamSet &ps)
    {
        // Extract the required parameters from the ParamSet object
        std::string type = retrieve(ps, "type", std::string{""});

        // Create a Material object based on the type
        Material *material = nullptr;
        if (type == "flat")
        {
            ColorXYZ color = retrieve(ps, "color", ColorXYZ{{0, 0, 0}});
            material = new FlatMaterial(color,1,1);
        }
        else if (type == "blinn")
        {
            ColorXYZ color = retrieve(ps, "color", ColorXYZ{0, 0, 0});
            Point3f ka = retrieve(ps, "ambient", Point3f{0, 0, 0});
            Point3f kd = retrieve(ps, "diffuse", Point3f{0, 0, 0});
            Point3f ks = retrieve(ps, "specular", Point3f{0, 0, 0});
            int ge = retrieve(ps, "glossiness", 100);
            material = new BlinnMaterial(color,1,1, ka, kd , ks, ge);
        }
        else
        {
            // Handle other Material types or throw an exception if the type is not supported
        }

        return material;
    }
}