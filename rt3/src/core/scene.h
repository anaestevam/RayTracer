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
    // Scene(std::shared_ptr<Camera> camera, std::shared_ptr<Background> background, std::vector<std::shared_ptr<Primitive>> primitives);
    Scene(const Camera &camera, const BackgroundColor &backgroundColor, const std::vector<std::shared_ptr<Primitive>> &primitives);

    std::shared_ptr<Camera> camera;
    // std::shared_ptr<Background> background;
    std::shared_ptr<BackgroundColor> backgroundColor;
    std::vector<std::shared_ptr<Primitive>> primitives;
  
  
  };
  Scene *create_scene();

  /*1)criar film_type
  2) criar camera
  3) criar cena )(que precisa da lista de objetos e bacjground)
  4)criar integrador
  5) the_integrator->render(*the_scene)


  */
}
#endif // SCENE_H
