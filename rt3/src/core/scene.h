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
  Scene(Camera* cam, BackgroundColor* &&bkg,
        std::vector<Primitive*> &&prim);
  // Scene(const Camera &camera, const BackgroundColor &backgroundColor, const
  // std::vector<std::shared_ptr<Primitive>> &primitives);

    Camera* camera;
    // std::shared_ptr<Background> background;
    BackgroundColor* backgroundColor;
    std::vector<Primitive*> primitives;
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