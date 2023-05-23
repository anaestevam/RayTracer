#ifndef RAY_H
#define RAY_H 1

#include "rt3.h"

class Ray
{
public:
    Ray(const Vector3f &o, const Vector3f &d,
        float start = 0, float end = INFINITY) : o{o}, d{d}, t_min{0.f}, t_max{INFINITY}
    { /*empty*/
    }
    
    Vector3f o;  //!< origin
    Vector3f d; //!< direction
    Ray() : t_min{0.f}, t_max{INFINITY}
    { /*empty*/
    }
    Ray(const Vector3f& origin_, const Vector3f& direction_, int i)
        : o(origin_), d(direction_), i(i)
    {
        float vertical_fov_degrees = 90.0;
        float aspect_ratio = 16.0 / 9.0;
        float viewport_height = 2.0 * tan(degrees_to_radians(vertical_fov_degrees) / 2.0);
        float viewport_width = aspect_ratio * viewport_height;
        //...
    }
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
        return o + d * t;
    }

    Vector3f origin_;
    Vector3f direction_;
    int i;
};

// Ray r{Point3f{0, 0, 0}, Vector3f{3, 2, -4}}; // creating an infinity ray.
// float t{2.3};                                // a parameter for the ray.
// Point3f p = r(t);                            // overloading operator()(), so that it returns o + t*d.

#endif // RAY_H