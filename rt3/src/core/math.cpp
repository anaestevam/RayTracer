#include "rt3.h"
#include "math.h"

namespace math
{
    ColorXYZ lerp(const ColorXYZ &A, const ColorXYZ &B, float t)
    {
        ColorXYZ new_color = {0, 0, 0};
        new_color[0] = (1 - t) * A[0] + t * B[0];
        new_color[1] = (1 - t) * A[1] + t * B[1];
        new_color[2] = (1 - t) * A[2] + t * B[2];
        return new_color;
    }

Vector3::Vector3(){
    for (int i = 0; i < 3; i++){
        this->vector[i] = 0;
    }
}

Vector3::Vector3(double x, double y, double z){
    this->vector[0] = x;
    this->vector[1] = y;
    this->vector[2] = z;
}

double &Vector3::operator[](int const k){
    return this->vector[k];
}

double Vector3::operator[](int const k) const{
    return this->vector[k];
}

Vector3 &operator/=(Vector3 &lhs, double const &rhs){
    lhs *= 1 / rhs;

    return lhs;
}

Vector3 &operator*=(Vector3 &lhs, double const &rhs){
    lhs.vector[0] *= rhs;
    lhs.vector[1] *= rhs;
    lhs.vector[2] *= rhs;

    return lhs;
}


Vector3 operator*(Vector3 const &lhs, double const rhs){
    Vector3 v;
    v.vector[0] = lhs.vector[0] * rhs;
    v.vector[1] = lhs.vector[1] * rhs;
    v.vector[2] = lhs.vector[2] * rhs;

    return v;
}

double operator*(Vector3 const &rhs, Vector3 const &lhs){
    Vector3 v;
    return (rhs[0] * lhs[0]) + (rhs[1] * lhs[1]) + (rhs[2] * lhs[2]);
}

Vector3 operator/(Vector3 const &lhs, double const rhs){
    double r = 1/rhs;
    Vector3 v;
    v.vector[0] = lhs.vector[0]*r;
    v.vector[1] = lhs.vector[1]*r;
    v.vector[2] = lhs.vector[2]*r;

    return v;
}

Vector3 operator*( double const rhs, Vector3 const &lhs){
    return lhs * rhs;
}

Vector3 &operator+=(Vector3 &lhs, Vector3 const &rhs){
    lhs.vector[0] += rhs.vector[0];
    lhs.vector[1] += rhs.vector[1];
    lhs.vector[2] += rhs.vector[2];

    return lhs;
}

Vector3 operator+(Vector3 const &lhs, Vector3 const &rhs){
    Vector3 temp = lhs;
    temp += rhs;
    return temp;
}

Vector3 &operator-=(Vector3 &lhs, Vector3 const &rhs){
    lhs.vector[0] -= rhs.vector[0];
    lhs.vector[1] -= rhs.vector[1];
    lhs.vector[2] -= rhs.vector[2];

    return lhs;
}

Vector3 operator-(Vector3 const &lhs, Vector3 const &rhs){
    Vector3 temp = lhs;
    temp -= rhs;
    return temp;
}

double Vector3::length(){
    return sqrt(this->length_squared());
}

double Vector3::length_squared(){
    return this->vector[0] * this->vector[0] + this->vector[1] * this->vector[1] + this->vector[2] * this->vector[2];
}

}