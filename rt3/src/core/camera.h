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
    virtual ~Camera() {}

    virtual Ray generate_ray(int x, int y) const = 0;

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
    PerspectiveCamera(const Vector3f& lookfrom, const Vector3f& lookat, const Vector3f& vup, float vfov, float aspect_ratio)
        : Camera(Film()), origin(lookfrom)
    {
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

    Ray generate_ray(int x, int y) const override
    {
        float u = float(x) / float(film.m_full_resolution[0]);
        float v = float(y) / float(film.m_full_resolution[1]);
        return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }

private:
    Vector3f origin;
    Vector3f lower_left_corner;
    Vector3f horizontal;
    Vector3f vertical;
    Vector3f u, v, w;
};

class OrthographicCamera : public Camera
{
public:
    OrthographicCamera(const Vector3f& lookfrom, const Vector3f& lookat, const Vector3f& vup, float height, float aspect_ratio)
        : Camera(Film()), origin(lookfrom)
    {
        float viewport_height = height;
        float viewport_width = aspect_ratio * viewport_height;

        w = Vector3f::unit_vector(lookfrom - lookat);
        u = Vector3f::unit_vector(Vector3f::cross(vup, w));
        v = Vector3f::cross(w, u);

        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
    }

    Ray generate_ray(int x, int y) const override
    {
        float u = float(x) / float(film.m_full_resolution[0]);
        float v = float(y) / float(film.m_full_resolution[1]);
        return Ray(lower_left_corner + u * horizontal + v * vertical, w);
    }

private:
    Vector3f origin;
    Vector3f lower_left_corner;
    Vector3f horizontal;
    Vector3f vertical;
    Vector3f u, v, w;
};

std::shared_ptr<Camera> create_perspective_camera(const Vector3f& lookfrom, const Vector3f& lookat, const Vector3f& vup, float vfov, float aspect_ratio)
{
    return std::make_shared<PerspectiveCamera>(lookfrom, lookat, vup, vfov, aspect_ratio);
}

std::shared_ptr<Camera> create_orthographic_camera(const Vector3f& lookfrom, const Vector3f& lookat, const Vector3f& vup, float height, float aspect_ratio)
{
    return std::make_shared<OrthographicCamera>(lookfrom, lookat, vup, height, aspect_ratio);

}
}
#endif // CAMERA_H
