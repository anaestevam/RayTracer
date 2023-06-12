#ifndef RAY_H
#define RAY_H 1

#include "rt3.h"

class Ray
{
public:
    Ray(const Point3f &o, const Vector3f &d,
        float start = 0, float end = INFINITY) : o{o}, d{d}, t_min{0.f}, t_max{INFINITY}
    { /*empty*/
    }

    Point3f o;  //!< origin
    Vector3f d; //!< direction
    Ray() : t_min{0.f}, t_max{INFINITY}
    { /*empty*/
    }
    Ray(const Point3f &origin_, const Vector3f &direction_, int i)
        : o(origin_), d(direction_), i(i)
    {
    }
    Point3f point_at_parameter(float t) const { return o + d * t; }
    Vector3f vector_at_parameter(float t) const { return d.ToVector3(o) + d * t; }

private:
    float t_min, t_max; //!< parameters
    Vector3f operator()(float t) const
    {
        return d.ToVector3(o) + d * t;
    }

    Point3f origin_;
    Vector3f direction_;
    int i;
};

#endif // RAY_H