#ifndef SCENE_H
#define SCENE_H 1

#include "background.h"
#include "camera.h"
#include "primitive.h"
#include <memory>
#include <vector>
namespace rt3
{
  class Scene
  {
  public:
  Scene(Camera* cam, std::unique_ptr<BackgroundColor> &&bkg,
        std::vector<std::shared_ptr<Primitive>> &&prim);
  // Scene(const Camera &camera, const BackgroundColor &backgroundColor, const
  // std::vector<std::shared_ptr<Primitive>> &primitives);

    std::shared_ptr<Camera> camera;
    // std::shared_ptr<Background> background;
    std::unique_ptr<BackgroundColor> backgroundColor;
    std::vector<std::shared_ptr<Primitive>> primitives;
  };
  //Scene *create_scene();

  /*1)criar film_type
  2) criar camera
  3) criar cena )(que precisa da lista de objetos e bacjground)
  4)criar integrador
  5) the_integrator->render(*the_scene)


  */
} // namespace rt3
#endif // SCENE_H
