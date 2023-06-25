#ifndef CAMERA_H
#define CAMERA_H 1

#include "ray.h"
#include "film.h"
#include "paramset.h"
#include "screen_window.h"

namespace rt3
{
class Camera{
public:
    Film *film;
    Point3f eye; // position of the camera
    Vector3f w, u, v;
    ScreenWindow sw;

    Camera(Film *film, Point3f eye, Point3f center, Vector3f up, ScreenWindow sw);
    
    pair<real_type, real_type> get_uv_pos(int i, int j);

    virtual Ray generate_ray(int x, int y) = 0;
    // virtual ~Camera() = 0;
};

class PerspectiveCamera : public Camera {
  public:
    PerspectiveCamera(Film *film, Point3f _eye, Point3f _center, Vector3f _up, ScreenWindow sw);
    ~PerspectiveCamera();
    
    Ray generate_ray(int x, int y);
};

class OrthographicCamera : public Camera {
  public:
    OrthographicCamera(Film *film, Point3f _eye, Point3f _center, Vector3f _up, ScreenWindow sw);
    ~OrthographicCamera();
    
    Ray generate_ray(int x, int y);
};

PerspectiveCamera* create_perspective_camera(
    const ParamSet& camera_ps,
    const ParamSet& ps_look_at, Film *film
);
OrthographicCamera* create_orthographic_camera(
    const ParamSet& camera_ps,
    const ParamSet& lookat_ps,  Film *film
);

} // namespace rt3
#endif // CAMERA_H