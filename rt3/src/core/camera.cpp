#include "camera.h"

namespace rt3{

OrthographicCamera* create_orthographic_camera(const ParamSet& ps_camera,const ParamSet& ps_look_at, Film &&the_film){
    return 0;
}
PerspectiveCamera* create_perspective_camera(const ParamSet& ps_camera,const ParamSet& ps_look_at, Film &&the_film){
    return 0;
}
}