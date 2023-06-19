#include "bounds3.h"
namespace rt3
{
    Bounds3 Bounds3::expand(const Bounds3 &b, float delta)
    {
        return Bounds3(b.pMin - Vector3f(delta, delta, delta),
                       b.pMax + Vector3f(delta, delta, delta));
    }

    Vector3f Bounds3::diagonal() const
    {
        return pMax - pMin;
    }

    float Bounds3::surface_area() const
    {
        Vector3f d = diagonal();
        return 2 * (d[0] * d[1] + d[0] * d[2] + d[1] * d[2]);
    }

    float Bounds3::volume() const
    {
        Vector3f d = diagonal();
        return d[0] * d[1] * d[2];
    }

    int Bounds3::maximum_extent() const
    {
        Vector3f d = diagonal();
        if (d[0] > d[1] && d[0] > d[2])
            return 0;
        else if (d[1] > d[2])
            return 1;
        else
            return 2;
    }

    Vector3f Bounds3::offset(const Vector3f &p) const
    {

        Vector3f o = p - pMin;

        if (pMax[0] > pMin[0])
            o[0] /= pMax[0] - pMin[0];
        if (pMax[1] > pMin[1])
            o[1] /= pMax[1] - pMin[1];
        if (pMax[2] > pMin[2])
            o[2] /= pMax[2] - pMin[2];
        return o;
    }

    void Bounds3::bounding_to_sphere(
        Vector3f *center, float *radius)
    {
        *center = (pMin + pMax) / 2;
        if (inside(*center, *this))
            *radius = pMax.distance(*center);
        else
            *radius = 0;
    }

} // namespace rt3
