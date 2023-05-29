#include "scene.h"

#include <utility>

namespace rt3{

  
Scene::Scene(Camera* cam, BackgroundColor* &&bkg,
        std::vector<Primitive*> &&prim)
        : camera(cam), backgroundColor(std::move(bkg)), primitives() {
    for (auto& p : prim) {
        primitives.emplace_back(*p);
    }
}

/*rt3::Scene::Scene(std::shared_ptr<Camera> camera, std::shared_ptr<Background> background, std::vector<std::shared_ptr<Primitive>> &primitives)
     : camera(camera), background(background), primitives(primitives)
 {
 }*/