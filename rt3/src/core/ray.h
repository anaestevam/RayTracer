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

private:
    float t_min, t_max; //!< parameters
    Point3f operator()(float t) const
    {
        return o + d * t;
    }
};

// Ray r{Point3f{0, 0, 0}, Vector3f{3, 2, -4}}; // creating an infinity ray.
// float t{2.3};                                // a parameter for the ray.
// Point3f p = r(t);                            // overloading operator()(), so that it returns o + t*d.

#endif // RAY_H
