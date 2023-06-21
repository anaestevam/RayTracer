#include <array>
#include <iostream>

class Vector3f;

class Point3f {
public:
    using DataType = std::array<float, 3>;

    Point3f() : data_{0.0f, 0.0f, 0.0f} {}
    Point3f(float x, float y, float z) : data_{x, y, z} {}

    float& operator[](size_t index) {
        return data_[index];
    }

    const float& operator[](size_t index) const {
        return data_[index];
    }

    Point3f operator+(const Point3f& other) const {
        return Point3f(data_[0] + other[0], data_[1] + other[1], data_[2] + other[2]);
    }

    Point3f operator-(const Point3f& other) const {
        return Point3f(data_[0] - other[0], data_[1] - other[1], data_[2] - other[2]);
    }

    Point3f operator*(float scalar) const {
        return Point3f(data_[0] * scalar, data_[1] * scalar, data_[2] * scalar);
    }

    Point3f operator/(float scalar) const {
        return Point3f(data_[0] / scalar, data_[1] / scalar, data_[2] / scalar);
    }

    friend std::ostream& operator<<(std::ostream& os, const Point3f& point) {
        os << "(" << point[0] << ", " << point[1] << ", " << point[2] << ")";
        return os;
    }

        float norm() const
    {
        return std::sqrt(data_[0] * data_[0] + data_[1] * data_[1] + data_[2] * data_[2]);
    }

    Point3f unit_vector() const
    {
        float magnitude = norm();
        if (magnitude == 0)
        {
            return Point3f(0, 0, 0);
        }
        return Point3f(data_[0] / magnitude, data_[1] / magnitude, data_[2] / magnitude);
    }

    Point3f normalized() const
    {
        float n = norm();
        return Point3f(data_[0] / n, data_[1] / n, data_[2] / n);
    }

    
    friend inline Point3f operator+(const Point3f& point, const Vector3f& vector);
    friend inline Point3f operator-(const Point3f& point, const Vector3f& vector);
    friend inline Vector3f operator*(const Vector3f& vector, const Point3f& point);

    DataType::iterator begin() {
        return data_.begin();
    }

    DataType::const_iterator begin() const {
        return data_.begin();
    }

    DataType::iterator end() {
        return data_.end();
    }

    DataType::const_iterator end() const {
        return data_.end();
    }

    Point3f(std::initializer_list<float> init_list) {
        if (init_list.size() == 3) {
            std::copy(init_list.begin(), init_list.end(), data_.begin());
        } else {
            throw std::invalid_argument("Initializer list must contain exactly 3 elements.");
        }
    }

private:
    DataType data_;
};

inline Point3f operator*(const Point3f &v1, const Point3f &v2)
{
    return Point3f(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}
