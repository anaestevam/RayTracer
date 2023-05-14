#ifndef MATH_H
#define MATH_H 1

#include "rt3.h"
#include <cmath>
#include <vector>

namespace math
{

  ColorXYZ lerp(const ColorXYZ &A, const ColorXYZ &B, float t);

class Vector3{
public:
    double vector[3];
    
    Vector3();

    Vector3(double x, double y, double z);

    double operator[](int k) const;

    double &operator[](int k);

    friend Vector3 &operator/=(Vector3 &lhs, double const &rhs);

    friend Vector3 &operator*=(Vector3 &lhs, double const &rhs);

    friend Vector3 &operator-=(Vector3 &lhs, Vector3 const &rhs);

    friend Vector3 &operator+=(Vector3 &lhs, Vector3 const &rhs);

    friend Vector3 operator-(Vector3 const &lhs, Vector3 const &rhs);

    friend Vector3 operator+(Vector3 const &lhs, Vector3 const &rhs);

    friend Vector3 operator*(Vector3 const &lhs, double const rhs);

    friend Vector3 operator*(double const rhs, Vector3 const &lhs);

    friend double operator*(Vector3 const &rhs, Vector3 const &lhs);

    friend Vector3 operator/(Vector3 const &lhs, double const rhs);

    double length();

    double length_squared();
};

}
#endif // MATH_H
