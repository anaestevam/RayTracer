#ifndef VISIBILITYTESTER_H
#define VISIBILITYTESTER_H 1

#include "surfaceinteraction.h"
#include "scene.h"
#include "ray.h"
#include "rt3.h"

class Scene;
namespace rt3
{
class VisibilityTester {

private:
    SurfaceInteraction p0;  
    SurfaceInteraction p1;  

public:

    VisibilityTester(
        SurfaceInteraction p0,
        SurfaceInteraction p1) 
        : p0{p0}, p1{p1} {}

    VisibilityTester(){  }

    ~VisibilityTester(){}

    bool unoccluded(const Scene &scene);

    std::shared_ptr<Ray> shoot_ray() const;

};
}
#endif // VISIBILITYTESTER_H