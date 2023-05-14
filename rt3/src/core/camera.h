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
            PerspectiveCamera(Film &&_film);
            ~PerspectiveCamera();
    
    };
    class OrthographicCamera : public Camera
    {
        public:
            OrthographicCamera(Film &&_film);
            ~OrthographicCamera();
    
    };

    OrthographicCamera* create_orthographic_camera(const ParamSet& ps_camera, const ParamSet& ps_look_at, Film &&the_film);
    PerspectiveCamera* create_perspective_camera(const ParamSet& ps_camera, const ParamSet& ps_look_at, Film &&the_film);

}
#endif // CAMERA_H
