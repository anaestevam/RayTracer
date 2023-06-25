#include "camera.h"

namespace rt3{
/*Camera geral*/
pair<real_type, real_type> Camera::get_uv_pos(int i, int j){
    real_type u_pos = sw.width() * (j + 0.5);
    u_pos /= film->width(); u_pos += sw.left;

    real_type v_pos = sw.height() * (i + 0.5);
    v_pos /= film->height(); v_pos += sw.bottom;

    return {u_pos, v_pos};
}

Camera::Camera(Film *_film, Point3f _eye, Point3f _center, Vector3f _up, ScreenWindow _sw):
    film(std::move(_film)), eye(_eye), sw(_sw){
        Vector3f gaze = gaze.ToVector3(_center) - _eye; 
        
        w = gaze.normalized();
        // std::cout << "w " << w.toString() << std::endl;
        u = _up.cross(w).normalized();
        // std::cout << "u " << u.toString() << std::endl;
        v = u.cross(w).normalized();
        // std::cout << "v " << v.toString() << std::endl;
}
/*camera perspectiva*/

Ray PerspectiveCamera::generate_ray(int i, int j){
    auto [u_, v_] = get_uv_pos(i, j);
    Vector3f direction = w + (u * u_) + (v * v_);
    return Ray(eye, direction);
}

PerspectiveCamera::PerspectiveCamera(
    Film *_film, Point3f _eye, Point3f _center, Vector3f _up, ScreenWindow _sw): 
    Camera(std::move(_film), _eye, _center, _up, _sw){}


PerspectiveCamera* create_perspective_camera(
    const ParamSet& camera_ps,
    const ParamSet& lookat_ps, Film *the_film
){

    ScreenWindow sw;

    if( camera_ps.count("screen_window")){
        sw = retrieve(camera_ps, "screen_window", ScreenWindow());
    }else if(camera_ps.count("fovy")){
        real_type fovy = Radians(retrieve(camera_ps, "fovy", real_type()));

        real_type aspect = the_film->get_aspect();
        real_type h = fabs(tan(fovy / 2));

        sw = ScreenWindow(
            h * aspect * -1,    // left
            h * aspect,         // right
            h * -1,             // bottom
            h                   // top
        );

        // std::cout << fovy << " " << tan(fovy/2) << " " << h << " " << aspect << std::endl;
        // std::cout << sw.left << " " << sw.right << " " << sw.top << " " << sw.bottom << std::endl;
    }else{
        RT3_ERROR("Can't compute screen window with given parameters.");
    }

    PerspectiveCamera* camera = new PerspectiveCamera(
        std::move(the_film),
        retrieve( lookat_ps, "look_from",  Point3f({0.0, 0.1, 0.0})),
        retrieve( lookat_ps, "look_at",    Point3f({0.0, 0.1, 0.0})),
        retrieve( lookat_ps, "up",         Vector3f({0.0, 0.1, 0.0})),
        sw
    );

    return camera;
}

/*camera orthographic */

Ray OrthographicCamera::generate_ray(int i, int j){
    auto [u_, v_] = get_uv_pos(i, j);
    Point3f origin = eye + (u * u_) + (v * v_);
    return Ray(origin, w);
}


OrthographicCamera::OrthographicCamera(
    Film *_film, Point3f _eye, Point3f _center, Vector3f _up, ScreenWindow _sw): 
    Camera(std::move(_film), _eye, _center, _up, _sw){}


OrthographicCamera* create_orthographic_camera(
    const ParamSet& camera_ps,
    const ParamSet& lookat_ps, Film *the_film
){

    OrthographicCamera* camera = new OrthographicCamera(
        std::move(the_film),
        retrieve( lookat_ps,   "look_from",        Point3f({0.0, 0.1, 0.0})),
        retrieve( lookat_ps,   "look_at",          Point3f({0.0, 0.1, 0.0})),
        retrieve( lookat_ps,   "up",               Vector3f({0.0, 0.1, 0.0})),
        retrieve( camera_ps,    "screen_window",    ScreenWindow())
    );

    return camera;
}

}