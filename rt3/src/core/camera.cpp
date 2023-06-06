#include "camera.h"

namespace rt3{


PerspectiveCamera* create_perspective_camera(const ParamSet &camera_ps, const ParamSet &lookat_ps, Film* film)
{
    Vector3f lookfrom = retrieve(camera_ps,"position", Vector3f(0, 0, 0));
    Vector3f lookat = retrieve(lookat_ps, "target", Vector3f(0, 0, -1));
    Vector3f vup = retrieve(camera_ps, "up", Vector3f(0, 1, 0));
    float vfov = retrieve(camera_ps,"fov", 90);
    float aspect_ratio = retrieve(camera_ps,"aspectratio", 1);
    
    return new PerspectiveCamera(lookfrom, lookat, vup, vfov, aspect_ratio, film);
}

OrthographicCamera * create_orthographic_camera(const ParamSet &camera_ps, const ParamSet &lookat_ps, Film* film)
{
    Vector3f lookfrom = retrieve(camera_ps,"position", Vector3f(0, 0, 0));
    Vector3f lookat = retrieve(lookat_ps,"target", Vector3f(0, 0, -1));
    Vector3f vup = retrieve(camera_ps,"up", Vector3f(0, 1, 0));
   float left = retrieve(camera_ps,"left", -1);
            float right = retrieve(camera_ps,"right", 1);
            float bottom = retrieve(camera_ps,"bottom", -1);
            float top = retrieve(camera_ps,"top", 1);
if (camera_ps.count("screen_window"))
    {

    std::vector<real_type> cw = retrieve(camera_ps, "screen_window", std::vector<real_type>{-1, 1, -1, 1});
           std::cout << ">>> Inside API::camera_ps.count("")()\n" <<  cw[0];

          left = cw[0];
     right = cw[1];
     bottom = cw[2];
     top = cw[3];
    }
    return new OrthographicCamera(lookfrom, lookat, vup, left, right, bottom, top, film);
}

}