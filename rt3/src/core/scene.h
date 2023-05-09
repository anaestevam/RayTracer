#ifndef SCENE_H
#define SCENE_H 1

#include <memory>
#include <vector>
#include "background.h"
#include "camera.h"
#include "primitive.h"
namespace rt3
{
  class Scene
  {
  public:
    // Scene(std::shared_ptr<Camera> camera, std::shared_ptr<Background> background, std::vector<std::shared_ptr<Primitive>> obj_list);
    Scene(const Camera &camera, const BackgroundColor &backgroundColor, const std::vector<std::shared_ptr<Primitive>> &obj_list);

    std::shared_ptr<Camera> camera;
    // std::shared_ptr<Background> background;
    std::shared_ptr<BackgroundColor> backgroundColor;
    std::vector<std::shared_ptr<Primitive>> obj_list;
  };
}
#endif // SCENE_H
