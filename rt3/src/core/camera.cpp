#include "camera.h"

namespace rt3{
/*Camera geral*/
pair<real_type, real_type> Camera::get_uv_pos(int i, int j){
    real_type u_pos = (real_type)(left) + (((real_type)(right-left) * (i + 0.5)) / film->width());

    real_type v_pos = (real_type)(bottom) + (((real_type)(top-bottom) * (j + 0.5)) / film->height());

    return {u_pos, v_pos};
}

Camera::Camera(Film *_film, Point3f _eye, Point3f _center, Vector3f _up, std::vector<real_type>& screen_space):
    film(std::move(_film)), eye(_eye),
		left{screen_space.at(0)}, right{screen_space.at(1)},
		bottom{screen_space.at(2)}, top{screen_space.at(3)}{
        Vector3f gaze = gaze.ToVector3(_center) - _eye; 
        
        w = gaze.normalized();
        u = _up.cross(w).normalized();
        v = u.cross(w).normalized();
}
/*camera perspectiva*/


PerspectiveCamera::PerspectiveCamera(
    Film *_film, Point3f _eye, Point3f _center, Vector3f _up, std::vector<real_type>& screen_space): 
    Camera(std::move(_film), _eye, _center, _up, screen_space){}


PerspectiveCamera* create_perspective_camera(
    const ParamSet& camera_ps,
    const ParamSet& lookat_ps, Film *the_film
){
	real_type fovy = retrieve(camera_ps, "fovy", real_type{30.0});
	Point3f look_from = retrieve(lookat_ps, "look_from", Point3f{0.0,0,0.0});
	Point3f look_at = retrieve(lookat_ps, "look_at", Point3f{0.0,0,-1});
	Vector3f up = retrieve(lookat_ps, "up", Vector3f{0.0,1,0.0});
		
	real_type aspect_ratio = the_film->get_aspect();

	real_type h = tan(Radians(fovy/2.0));
	std::cout << "valor do fovy: " << fovy << std::endl;
	std::cout << "valor do h: " << h << std::endl;
		
	std::vector<real_type> values = std::vector<real_type>{-1 * aspect_ratio*h, aspect_ratio*h, -1 * h, h};
		

	std::cout << "screen space: " << values[0] << " "
	<< values[1] << " "
	<< values[2] << " "
	<< values[3] << " " << std::endl;

    PerspectiveCamera* camera = new PerspectiveCamera(
        std::move(the_film), look_from, look_at, up, values
    );

    return camera;
}

Ray PerspectiveCamera::generate_ray(int i, int j){
    auto [u_, v_] = get_uv_pos(i, j);
    Vector3f direction = w + (u * u_) + (v * v_);
    return Ray(eye, direction);
}
/*camera orthographic */



OrthographicCamera::OrthographicCamera(
    Film *_film, Point3f _eye, Point3f _center, Vector3f _up, std::vector<real_type>& screen_space): 
    Camera(std::move(_film), _eye, _center, _up, screen_space){}


OrthographicCamera* create_orthographic_camera(
    const ParamSet& camera_ps,
    const ParamSet& lookat_ps, Film *the_film
){
    std::vector<real_type> values = retrieve(camera_ps, "screen_window", std::vector<real_type>{0.0,0.0,0.0,0.0});
		
    OrthographicCamera* camera = new OrthographicCamera(
        std::move(the_film),
        retrieve( lookat_ps,   "look_from",        Point3f({0.0, 0, 0.0})),
        retrieve( lookat_ps,   "look_at",          Point3f({0.0, 0, -1})),
        retrieve( lookat_ps,   "up",               Vector3f({0.0, 1, 0.0})),
        values
    );

    return camera;
}
Ray OrthographicCamera::generate_ray(int i, int j){
    auto [u_, v_] = get_uv_pos(i, j);
    Point3f origin = eye + (u * u_) + (v * v_);
    return Ray(origin, w);
}
}