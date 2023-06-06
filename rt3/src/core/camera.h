#ifndef CAMERA_H
#define CAMERA_H 1

#include "ray.h"
#include "film.h"
#include "paramset.h"

namespace rt3
{
    class Camera
    {
    public:
        Camera(Film *film_) : film(film_) {}

    virtual ~Camera() = default;

    [[nodiscard]] virtual Ray generate_ray(int x, int y) const = 0;

     Film* film;

    };


class PerspectiveCamera : public Camera {
public:
  PerspectiveCamera(const Vector3f &lookfrom, const Vector3f &lookat,
                    const Vector3f &vup, float vfov, float aspect_ratio,
                    Film *film)
      : Camera(film), origin(lookfrom) {
    float theta = Radians(vfov);
    float h = tan(theta / 2);
    float viewport_height = 2.0 * h;
    float viewport_width = aspect_ratio * viewport_height;

    w = (lookfrom - lookat).unit_vector();
    u = vup.cross(w).unit_vector();
    v = w.cross(u);

    horizontal = u * viewport_width;
    vertical = v * viewport_height;
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
  }


  Ray generate_ray(int x, int y) const override {
        float u = float(x) / float(film->m_full_resolution[0]);
        float v = float(y) / float(film->m_full_resolution[1]);
        const Vector3f direction = (lower_left_corner + horizontal * u + vertical * v) - origin;
        return Ray(origin.ToPoint3(),  direction, 0.0f);
    }


private:
    Vector3f origin;
    Vector3f lower_left_corner;
    Vector3f horizontal;
    Vector3f vertical;
    Vector3f u, v, w;
};

class OrthographicCamera : public Camera {
public:
  OrthographicCamera(const Vector3f &lookfrom, const Vector3f &lookat,
                 const Vector3f &vup, float left, float right, float bottom,
                 float top, Film *film)
  : Camera(film), origin(lookfrom) {
  this->left = left;
  this->right = right;
  this->bottom = bottom;
  this->top = top;

  w = (lookfrom - lookat).unit_vector();
  u = vup
    .cross(w)
    .unit_vector();
  v = w.cross(u);

  float viewport_width = (right - left);
  float viewport_height = (top - bottom);

  horizontal = viewport_width * u;
  vertical = viewport_height * v;
  lower_left_corner = origin - horizontal / (2.0f * film->m_full_resolution[0]) - vertical / (2.0f * film->m_full_resolution[1]) - w;
}


  Ray generate_ray(int x, int y) const override {
    float u = float(x) / float(film->m_full_resolution[0]);
    float v = float(y) / float(film->m_full_resolution[1]);
    return Ray((lower_left_corner + (horizontal * u) + (vertical * v)).ToPoint3(), w, 0);
  }

private:
    Vector3f origin;
    Vector3f lower_left_corner;
    Vector3f horizontal;
    Vector3f vertical;
    Vector3f u, v, w;
    float left, bottom, right, top;
};

PerspectiveCamera *create_perspective_camera(const ParamSet &camera_ps,
                                             const ParamSet &lookat_ps,
                                             Film *film);
OrthographicCamera *create_orthographic_camera(const ParamSet &camera_ps,
                                               const ParamSet &lookat_ps,
                                               Film *film);

} // namespace rt3
#endif // CAMERA_H