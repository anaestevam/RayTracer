#include "scene.h"

#include <utility>

namespace rt3{

  
Scene::Scene(Camera* cam, BackgroundColor* &&bkg, const std::vector<Sphere*>& prim/*, const std::vector<Light *> &lights*/)
        : camera(cam), backgroundColor(std::move(bkg)), primitives() {
    for (auto& p : prim) {
        primitives.emplace_back(p);
    }
}
}