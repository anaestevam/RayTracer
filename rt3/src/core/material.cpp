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
        else
        {
            // Handle other Material types or throw an exception if the type is not supported
        }

        return material;
    }
}