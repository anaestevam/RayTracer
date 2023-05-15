#include <array>
#include <iostream>

class Vector3f {
public:
    using DataType = std::array<float, 3>;

    Vector3f() : data_{0.0f, 0.0f, 0.0f} {}
    Vector3f(float x, float y, float z) : data_{x, y, z} {}

    float& operator[](size_t index) {
        return data_[index];
    }

    const float& operator[](size_t index) const {
        return data_[index];
    }

    Vector3f operator+(const Vector3f& other) const {
        return Vector3f(data_[0] + other[0], data_[1] + other[1], data_[2] + other[2]);
    }

    Vector3f operator-(const Vector3f& other) const {
        return Vector3f(data_[0] - other[0], data_[1] - other[1], data_[2] - other[2]);
    }

    Vector3f operator*(float scalar) const {
        return Vector3f(data_[0] * scalar, data_[1] * scalar, data_[2] * scalar);
    }

    Vector3f operator/(float scalar) const {
        return Vector3f(data_[0] / scalar, data_[1] / scalar, data_[2] / scalar);
    }

    float dot(const Vector3f& other) const {
        return data_[0] * other[0] + data_[1] * other[1] + data_[2] * other[2];
    }

    Vector3f cross(const Vector3f& other) const {
        return Vector3f(data_[1] * other[2] - data_[2] * other[1],
                         data_[2] * other[0] - data_[0] * other[2],
                         data_[0] * other[1] - data_[1] * other[0]);
    }

    float norm() const {
        return std::sqrt(data_[0] * data_[0] + data_[1] * data_[1] + data_[2] * data_[2]);
    }

    Vector3f normalized() const {
        float n = norm();
        return Vector3f(data_[0] / n, data_[1] / n, data_[2] / n);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3f& vector) {
        os << "(" << vector[0] << ", " << vector[1] << ", " << vector[2] << ")";
        return os;
    }

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

    Vector3f(std::initializer_list<float> init_list) {
        if (init_list.size() == 3) {
            std::copy(init_list.begin(), init_list.end(), data_.begin());
        } else {
            throw std::invalid_argument("Initializer list must contain exactly 3 elements.");
        }
    }
    

private:
    DataType data_;
};


  inline Point3f operator+(const Point3f& point, const Vector3f& vector) {
        return Point3f(point[0] + vector[0], point[1] + vector[1], point[2] + vector[2]);
    }