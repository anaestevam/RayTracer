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

    Film *film;
  };

  class PerspectiveCamera : public Camera
  {
  public:
    PerspectiveCamera(const Vector3f &lookfrom, const Vector3f &lookat,
                      const Vector3f &vup, float vfov, float a,
                      Film *film)
        : Camera(film), origin(lookfrom)
    {
      float theta = vfov;
      float h = fabs(tan(theta));

            this->left = -a *h;
      this->right = a *h;
      this->bottom = -h;
      this->top = h;
      


      w = (lookat - lookfrom).normalized();
      u = vup.cross(w).normalized();
      v = w.cross(u).normalized();

      e = lookfrom;
    }

    Ray generate_ray(int x, int y) const override
    {
       auto width = film->m_full_resolution[0];
      auto height = film->m_full_resolution[1];

      float u_ = left + (((right - left) * (x + 0.5)) / width);
      float v_ = bottom + (((top - bottom) * (y + 0.5)) / height);
      const Vector3f direction = (w + (u * u_) + (v * v_));
      return Ray(e.ToPoint3(), direction , 0.0f);
    }

  private:
    Vector3f origin;
    Vector3f lower_left_corner;
    Vector3f horizontal;
    Vector3f vertical;
    Vector3f u, v, w, e;
        float left, bottom, right, top;

  };

  class OrthographicCamera : public Camera
  {
  public:
    OrthographicCamera(const Vector3f &lookfrom, const Vector3f &lookat,
                       const Vector3f &vup, float left, float right, float bottom,
                       float top, Film *film)
        : Camera(film), origin(lookfrom),  direction(lookat)
    {
      this->left = left;
      this->right = right;
      this->bottom = bottom;
      this->top = top;
           std::cout << ">>> Inside API::camera_ps.count("")()" <<  left;

      // mapping pixels to screen space

      w = (lookat - lookfrom).normalized();
      u = vup.cross(w).normalized();
      v = w.cross(u).normalized();

      e = lookfrom;

      // horizontal = viewport_width * u;
      // vertical = viewport_height * v;
      // lower_left_corner = origin - horizontal / (2.0f * film->m_full_resolution[0]) - vertical / (2.0f * film->m_full_resolution[1]) - w;
    }

    Ray generate_ray(int x, int y) const override
    {

       auto width = film->m_full_resolution[0];
      auto height = film->m_full_resolution[1];

      float u_ = left + ((right - left) * (x + 0.5)) / width;
      float v_ = bottom + ((top - bottom) * (y + 0.5)) / height;
      
      const Vector3f origin = (e + (u * u_) + (v * v_));

      return Ray(origin.ToPoint3(), w, 0);
    }

  private:
    Vector3f origin;
    Vector3f direction;
    Vector3f lower_left_corner;
    Vector3f horizontal;
    Vector3f vertical;
    Vector3f u, v, w, e;
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