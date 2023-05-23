#include "camera.h"

namespace rt3{

/*Ray PerspectiveCamera::generate_ray(int x, int y) const
{
    // Implement ray generation logic for perspective camera
}

Ray OrthographicCamera::generate_ray(int x, int y) const
{
    // Implement ray generation logic for orthographic camera
}*/

std::shared_ptr<Camera> create_perspective_camera(const ParamSet &camera_ps, const ParamSet &lookat_ps, Film* film)
{
    Vector3f lookfrom = retrieve(camera_ps,"position", Vector3f(0, 0, 0));
    Vector3f lookat = retrieve(lookat_ps, "target", Vector3f(0, 0, -1));
    Vector3f vup = retrieve(camera_ps, "up", Vector3f(0, 1, 0));
    float vfov = retrieve(camera_ps,"fov", 90);
    float aspect_ratio = retrieve(camera_ps,"aspectratio", 1);
    float aperture = retrieve(camera_ps,"aperture", 0);
    float focus_distance = retrieve(camera_ps,"focusdistance", 1);

    return std::make_shared<PerspectiveCamera>(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, focus_distance);
}

std::shared_ptr<Camera> create_orthographic_camera(const ParamSet &camera_ps, const ParamSet &lookat_ps, Film* film)
{
    Vector3f lookfrom = retrieve(camera_ps,"position", Vector3f(0, 0, 0));
    Vector3f lookat = retrieve(lookat_ps,"target", Vector3f(0, 0, -1));
    Vector3f vup = retrieve(camera_ps,"up", Vector3f(0, 1, 0));
    float left = retrieve(camera_ps,"left", -1);
    float right = retrieve(camera_ps,"right", 1);
    float bottom = retrieve(camera_ps,"bottom", -1);
    float top = retrieve(camera_ps,"top", 1);

    return std::make_shared<OrthographicCamera>(lookfrom, lookat, vup, left, right, bottom, top);
}

}