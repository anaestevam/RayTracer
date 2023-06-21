#ifndef POINT_LIGHT
#define POINT_LIGHT

#include "light.h"
#include "../rt3.h"
#include "../paramset.h"

namespace rt3
{
class PointLight : public Light {

public:
    Point3f direction; 
    Point3f position;

    PointLight(const Color &c, const Vector3f &scl, const Point3f &pos):
        SamplerLight(c, scl), position(pos){}

    
    tuple<Color, unique_ptr<VisibilityTester>, Vector3f> Li(const shared_ptr<Surfel>& hit) override;


};
 PointLight* create_point_light(const ParamSet& ps);

} // namespace rt3

#endif
//construtor point intensidade e position
//create_point_light retorna a position, scala * intensidade

