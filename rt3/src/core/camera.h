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

        Ray generate_ray(int x, int y) const
        {
            // Implement ray generation logic based on camera parameters and pixel coordinates
        }

    private:
        Film film_;
    };

    class PerspectiveCamera : public Camera
    {
        // ...
    };
    class OrthographicCamera : public Camera
    {
        // ...
    };
}
#endif // CAMERA_H
