#include "visibilitytester.h"
#include "surfaceinteraction.h"

namespace rt3
{
bool VisibilityTester::unoccluded(
    const Scene &scene)
{
    return !scene.intersect(*shoot_ray().get(), &this->p1);
}

std::shared_ptr<Ray> VisibilityTester::shoot_ray() const 
{
    Point3f origin = p0.p;
    Point3f destiny = p1.p;
    Vector3f a{0,0,0};
    Vector3f v = a.ToVector3(destiny - origin);

    std::shared_ptr<Ray> r (new Ray(origin, v,0,1));
    return  r;
}
}