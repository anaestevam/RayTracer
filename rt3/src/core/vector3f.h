#include <array>
#include <iostream>
#include <random>
#include <math.h>
#include <stdlib.h>
#include <random>

class Vector3f
{
public:
    using DataType = std::array<float, 3>;

    Vector3f() : data_{0.0f, 0.0f, 0.0f} {}
    Vector3f(float x, float y, float z) : data_{x, y, z} {}

    Point3f ToPoint3()
    {
        return Point3f(data_[0], data_[1], data_[2]);
    }

    const Point3f ToPoint3() const
    {
        return Point3f(data_[0], data_[1], data_[2]);
    }

    Vector3f ToVector3(Point3f point)
    {
        return Vector3f(point[0], point[1], point[2]);
    }

    const Vector3f ToVector3(const Point3f point) const
    {
        return Vector3f(point[0], point[1], point[2]);
    }

    float &operator[](size_t index)
    {
        return data_[index];
    }

    const float &operator[](size_t index) const
    {
        return data_[index];
    }

    Vector3f operator+(const Vector3f &other) const
    {
        return Vector3f(data_[0] + other[0], data_[1] + other[1], data_[2] + other[2]);
    }

    Vector3f operator-(const Vector3f &other) const
    {
        return Vector3f(data_[0] - other[0], data_[1] - other[1], data_[2] - other[2]);
    }

    Vector3f operator*(float scalar) const
    {
        return Vector3f(data_[0] * scalar, data_[1] * scalar, data_[2] * scalar);
    }

    Vector3f operator/(float scalar) const
    {
        return Vector3f(data_[0] / scalar, data_[1] / scalar, data_[2] / scalar);
    }

    bool operator==(const Vector3f &other) const
    {
        return data_[0] == other.data_[0] &&
               data_[1] == other.data_[1] &&
               data_[2] == other.data_[2];
    }

    float *const operator*(const Vector3f &other) const
    {
        float *result = new float[3];
        result[0] = data_[0] * other[0];
        result[1] = data_[1] * other[1];
        result[2] = data_[2] * other[2];
        return result;
    }

    float dot(const Vector3f &other) const
    {
        return (data_[0] * other[0]) + (data_[1] * other[1]) + (data_[2] * other[2]);
    }

    Vector3f cross(const Vector3f &other) const
    {
        return Vector3f(data_[1] * other[2] - data_[2] * other[1],
                        ( - data_[2]) * other[0] - data_[0] * other[2],
                        data_[0] * other[1] - data_[1] * other[0]);
    }

    float norm() const
    {
        return std::sqrt(data_[0] * data_[0] + data_[1] * data_[1] + data_[2] * data_[2]);
    }

    Vector3f unit_vector() const
    {
        float magnitude = norm();
        if (magnitude == 0)
        {
            return Vector3f(0, 0, 0);
        }
        return Vector3f(data_[0] / magnitude, data_[1] / magnitude, data_[2] / magnitude);
    }

    Vector3f normalized() const
    {
        float n = norm();
        return Vector3f(data_[0] / n, data_[1] / n, data_[2] / n);
    }

    float degrees_to_radians(float degrees)
    {
        return degrees * M_PI / 180.0;
    }

    inline float distance(Vector3f &p2)
    {
        return sqrt(pow((data_[0] - p2[0]), 2) +
                    pow((data_[1] - p2[1]), 2) +
                    pow((data_[2] - p2[2]), 2));
    }

    static Vector3f unit_vector(Vector3f v)
    {
        return v / v.length();
    }

    static double random_double()
    {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector3f &vector)
    {
        os << "(" << vector[0] << ", " << vector[1] << ", " << vector[2] << ")";
        return os;
    }

    DataType::iterator begin()
    {
        return data_.begin();
    }

    DataType::const_iterator begin() const
    {
        return data_.begin();
    }

    DataType::iterator end()
    {
        return data_.end();
    }

    DataType::const_iterator end() const
    {
        return data_.end();
    }

    Vector3f(std::initializer_list<float> init_list)
    {
        if (init_list.size() == 3)
        {
            std::copy(init_list.begin(), init_list.end(), data_.begin());
        }
        else
        {
            throw std::invalid_argument("Initializer list must contain exactly 3 elements.");
        }
    }

    
 double length()
{
    return sqrt(length_squared());
}

 double length_squared() const
{
    return data_[0] * data_[0] + data_[1] * data_[1] + data_[2] * data_[2];
}

    inline const Vector3f &operator+() const { return *this; }
    inline Vector3f operator-() const { return Vector3f(-data_[0], -data_[1], -data_[2]); }
    inline float operator[](int i) const { return data_[i]; }
    inline float &operator[](int i) { return data_[i]; };

    inline Vector3f &operator+=(const Vector3f &v2);
    inline Vector3f &operator-=(const Vector3f &v2);
    inline Vector3f &operator*=(const Vector3f &v2);
    inline Vector3f &operator/=(const Vector3f &v2);
    inline Vector3f &operator*=(const float t);
    inline Vector3f &operator/=(const float t);

    inline float length() const { return sqrt(data_[0] * data_[0] + data_[1] * data_[1] + data_[2] * data_[2]); }
    inline float squared_length() const { return data_[0] * data_[0] + data_[1] * data_[1] + data_[2] * data_[2]; }
    inline void make_unit_vector();
    inline double random_double_a();
    inline double random_double(double min, double max);
    inline Vector3f random(double min, double max);
    inline Vector3f random_in_unit_sphere();
    float e[3];

private:
    DataType data_;
};

inline float degrees_to_radians(float degrees)
{
    return degrees * M_PI / 180.0;
}

inline Point3f operator+(const Point3f &point, const Vector3f &vector)
{
    return Point3f(point[0] + vector[0], point[1] + vector[1], point[2] + vector[2]);
}

inline Point3f operator-(const Point3f &point, const Vector3f &vector)
{
    return Point3f(point[0] - vector[0], point[1] - vector[1], point[2] - vector[2]);
}

inline Vector3f operator*(const Vector3f &vector, const Point3f &point)
{
    return Vector3f(point[0] * vector[0], point[1] * vector[1], point[2] * vector[2]);
}
inline Vector3f operator*(const Vector3f &v1, const Vector3f &v2)
{
    return Vector3f(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}
/*inline Vector3f operator*(const Vector3f& v, float t) {
    return Vector3f(t*v[0], t*v[1], t*v[2]);
}*/
inline Vector3f operator*(float t, const Vector3f &v)
{
    return Vector3f(t * v[0], t * v[1], t * v[2]);
}
inline Vector3f operator-(const Vector3f &v1, const Point3f &point)
{
    return Vector3f(v1[0] - point[0], v1[1] - point[1], v1[2] - point[2]);
}

inline Point3f operator*(const Point3f &v1, const Vector3f &v2)
{
    return Point3f(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

inline void Vector3f::make_unit_vector()
{
    float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

inline double Vector3f::random_double_a() {
    return rand() / (RAND_MAX + 1.0);
}

inline double Vector3f::random_double(double min, double max)
{
    return min + (max - min) * random_double_a();
}

inline Vector3f Vector3f::random(double min, double max)
{
    return Vector3f(random_double(min, max), random_double(min, max), random_double(min, max));
}


inline Vector3f Vector3f::random_in_unit_sphere()
{
    while (true)
    {
        double x = random_double(-1, 1);
        double y = random_double(-1, 1);
        double z = random_double(-1, 1);
        Vector3f p(x, y, z);
        if (p.length_squared() >= 1)
            continue;
        return p;
    }
}
