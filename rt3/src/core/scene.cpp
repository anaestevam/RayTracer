#include "scene.h"

rt3::Scene::Scene(const Camera &camera, const BackgroundColor &backgroundColor, const std::vector<std::shared_ptr<Primitive>> &primitives)
    : camera(std::make_shared<Camera>(camera)), backgroundColor(std::shared_ptr<BackgroundColor>(new BackgroundColor(backgroundColor))), primitives(primitives)
{
}

// rt3::Scene::Scene(std::shared_ptr<Camera> camera, std::shared_ptr<Background> background, std::vector<std::shared_ptr<Primitive>> obj_list)
//     : camera(camera), background(background), obj_list(obj_list)
// {
// }
