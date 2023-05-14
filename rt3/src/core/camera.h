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
    public:
        PerspectiveCamera(const ParamSet &params, const Film &film_)
            : Camera(film_)
        {
            // Extract camera parameters from the ParamSet
            // ...

            // Calculate the camera-to-world transformation matrix
            // ...

            // Calculate the image plane dimensions
            // ...

            // Calculate the distance from the camera to the image plane
            // ...

            // Calculate the direction vectors for the image plane
            // ...

            // Calculate the ray direction based on the image plane and pixel coordinates
            // ...

            // Transform the ray direction to world space
            // ...

            // Create and return a new ray
            // ...
        }

    private:
        // Define private member variables for the camera parameters
        // ...
    };
    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera(const ParamSet &params, const Film &film_)
            : Camera(film_)
        {
            // Extract camera parameters from the ParamSet
            // ...

            // Calculate the camera-to-world transformation matrix
            // ...

            // Calculate the image plane dimensions
            // ...

            // Calculate the direction vectors for the image plane
            // ...
        }

    private:
        // Define private member variables for the camera parameters
        // ...
    };


    OrthographicCamera* create_orthographic_camera(const ParamSet& ps_camera, const ParamSet& ps_look_at, Film &&the_film);
    PerspectiveCamera* create_perspective_camera(const ParamSet& ps_camera, const ParamSet& ps_look_at, Film &&the_film);

    }
#endif // CAMERA_H
