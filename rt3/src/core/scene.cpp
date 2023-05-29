#include "scene.h"

#include <utility>

namespace rt3{
Scene::Scene(Camera* cam,
                  std::unique_ptr<BackgroundColor> &&bkg,
                  std::vector<std::shared_ptr<Primitive>> &&prim)
    : camera(cam), backgroundColor(std::move(bkg)),
      primitives(std::move(prim)) {}
}

/*rt3::Scene::Scene(std::shared_ptr<Camera> camera, std::shared_ptr<Background> background, std::vector<std::shared_ptr<Primitive>> &primitives)
     : camera(camera), background(background), primitives(primitives)
 {
 }*/
