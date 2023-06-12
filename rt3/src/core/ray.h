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
    Ray(const Point3f& origin_, const Vector3f& direction_, int i)
        : o(origin_), d(direction_), i(i)
    {
  
    }
    Point3f point_at_parameter(float t) const { return o + d * t; }

    /*Ray() {}
    Ray(const Vector3f& origin, const Vector3f& direction, int b) { A = origin; B = direction; b = 0;}
    Vector3f origin() const       { return A; }
    Vector3f direction() const    { return B; }
    Vector3f point_at_parameter(float t) const { return A + t*B; }

    Vector3f A;
    Vector3f B;*/

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

// Ray r{Point3f{0, 0, 0}, Vector3f{3, 2, -4}}; // creating an infinity ray.
// float t{2.3};                                // a parameter for the ray.
// Point3f p = r(t);                            // overloading operator()(), so that it returns o + t*d.

#endif // RAY_H