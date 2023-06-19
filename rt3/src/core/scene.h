#ifndef SCENE_H
#define SCENE_H 1

#include "background.h"
#include "camera.h"
#include "primitive.h"
#include "sphere.h"
#include <memory>
#include <vector>
namespace rt3
{
  class Scene
  {
  public:
    Scene(Camera *cam, BackgroundColor *&&bkg, const std::vector<Sphere *> &prim);

    Camera *camera;
    // std::shared_ptr<Background> background;
    BackgroundColor *backgroundColor;
    std::vector<Sphere *> primitives;
    std::vector<Light *> lights;

    bool intersect(const Ray &r, SurfaceInteraction *surface) const
    {
      for (const auto &primitive : primitives)
      {
        return primitive->intersect(r, surface);
      }
    }
  };
}
#endif