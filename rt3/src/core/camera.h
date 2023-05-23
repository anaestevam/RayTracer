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
        Camera(const Film &film_) : film(film_.m_full_resolution, film_.m_filename, film_.m_image_type) {}

        Film film;

    Camera(Vector3f lookfrom, Vector3f lookat, Vector3f vup, float vfov, float aspect_ratio, float aperture, float focus_distance) {
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
   }
        Ray generate_ray(int x, int y) const
        {
            // Implement ray generation logic based on camera parameters and pixel coordinates

            return Ray(origin_, lower_left_corner_ + x * horizontal_ + y * vertical_ - origin_, 0);
        }


    private:
        Film film_;
        Vector3f origin_;
        Vector3f lower_left_corner_;
        Vector3f horizontal_;
        Vector3f vertical_;
        Vector3f u_, v_, w_;
        float lens_radius_;
    };

    class PerspectiveCamera : public Camera
{
    public:
        PerspectiveCamera(const ParamSet &params, const Film &film_)
            : Camera(film_)
        {

        } 

    private:

    };
    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera(const ParamSet &params, const Film &film_)
            : Camera(film_)
        {

        }

    private:

    };



std::shared_ptr<Camera> create_perspective_camera(const ParamSet &camera_ps, const ParamSet &lookat_ps, Film* film);
std::shared_ptr<Camera> create_orthographic_camera(const ParamSet &camera_ps, const ParamSet &lookat_ps, Film* film);

    }
#endif // CAMERA_H
