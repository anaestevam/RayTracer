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
        Camera(const Film &film_2) : film2(film_2.m_full_resolution, film_2.m_filename, film_2.m_image_type) {}

    /*Camera(Vector3f lookfrom, Vector3f lookat, Vector3f vup, float vfov, float aspect_ratio, float aperture, float focus_distance) {
       float theta = degrees_to_radians(vfov);
       float h = tan(theta / 2);
       float viewport_height = 2.0 * h;
       float viewport_width = aspect_ratio * viewport_height;

       w_ = Vector3f::unit_vector(lookfrom - lookat);
       u_ = Vector3f::unit_vector(Vector3f::cross(vup, w_));
       v_ = Vector3f::cross(w_, u_);

       origin_ = lookfrom;
       horizontal_ = focus_distance * viewport_width * u_;
       vertical_ = focus_distance * viewport_height * v_;
       lower_left_corner_ = origin_ - horizontal_ / 2 - vertical_ / 2 - focus_distance * w_;

       lens_radius_ = aperture / 2;
   }*/
        /*Ray generate_ray(int x, int y) const
        {
            // Implement ray generation logic based on camera parameters and pixel coordinates

            return Ray(origin_, lower_left_corner_ + x * horizontal_ + y * vertical_ - origin_, 0);
        }*/
    virtual ~Camera() = default;

    [[nodiscard]] virtual Ray generate_ray(int x, int y) const = 0;

     std::unique_ptr<Film> film;

     Film film2;

    private:
        Film film_2;
        /*Vector3f origin_;
        Vector3f lower_left_corner_;
        Vector3f horizontal_;
        Vector3f vertical_;
        Vector3f u_, v_, w_;
        float lens_radius_;*/
    };

class PerspectiveCamera : public Camera {
public:
  PerspectiveCamera(const Vector3f &lookfrom, const Vector3f &lookat,
                    const Vector3f &vup, float vfov, float aspect_ratio,
                    Film *film)
      : Camera(film), origin(lookfrom) {
    float theta = degrees_to_radians(vfov);
    float h = tan(theta / 2);
    float viewport_height = 2.0 * h;
    float viewport_width = aspect_ratio * viewport_height;

    w = Vector3f::unit_vector(lookfrom - lookat);
    u = Vector3f::unit_vector(Vector3f::cross(vup, w));
    v = Vector3f::cross(w, u);

    horizontal = viewport_width * u;
    vertical = viewport_height * v;
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
  }

  [[nodiscard]] Ray generate_ray(int x, int y) const override {
    float u = float(x) / float(film->m_full_resolution[0]);
    float v = float(y) / float(film->m_full_resolution[1]);
    return {origin, lower_left_corner + u * horizontal + v * vertical - origin};
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

    w = Vector3f::unit_vector(lookfrom - lookat);
    u = Vector3f::unit_vector(Vector3f::cross(vup, w));
    v = Vector3f::cross(w, u);

    // horizontal = viewport_width * u;
    // vertical = viewport_height * v;
    // lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
  }

  [[nodiscard]] Ray generate_ray(int x, int y) const override {
    float u = float(x) / float(film->m_full_resolution[0]);
    float v = float(y) / float(film->m_full_resolution[1]);
    return {lower_left_corner + u * horizontal + v * vertical, w};
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
