#include "api.h"
#include "background.h"
#include "scene.h"
#include "sphere.h"
#include "paramset.h"
#include "ray.h"
#include "lights/ambientlight.h"
#include "lights/light.h"
#include "integrator/samplerintegrator.h"
#include "integrator/depthintegrator.h"
#include "integrator/normalintegrator.h"
#include "integrator/blinnphongintegrator.h"
#include "material.h"

#include <chrono>
#include <memory>

namespace rt3
{

  API::APIState API::curr_state = APIState::Uninitialized;
  RunningOptions API::curr_run_opt;
  std::unique_ptr<RenderOptions> API::render_opt;
  GraphicsState API::curr_GS;

  Film *API::make_film(const std::string &name, const ParamSet &ps)
  {
    std::cout << ">>> Inside API::make_film()\n";
    Film *film{nullptr};
    film = create_film(ps);

    return film;
  }

  BackgroundColor *API::make_background(const std::string &name, const ParamSet &ps)
  {
    std::cout << ">>> Inside API::background()\n";
    BackgroundColor *bkg{nullptr};
    bkg = create_color_background(ps, new BackgroundColor());

    return bkg;
  }

  std::vector<rt3::Primitive> API::make_primitives(const std::vector<ParamSet> &object_ps, const std::vector<ParamSet> &object_material_ps)
  {
    std::cout << ">>> Inside API::make_primitives()\n";
    std::vector<rt3::Material *> materials;

    for (const auto &ps : object_material_ps)
    {

      materials.push_back(create_material(ps));
    }

    std::vector<rt3::Primitive> primitives;
    for (size_t i = 0; i < object_ps.size(); ++i)
    {
      std::unique_ptr<rt3::Primitive> primitive_ptr = create_primitive(object_ps[i], materials[i]);

      rt3::Primitive *primitive_raw_ptr = primitive_ptr.release();

      primitives.emplace_back(*primitive_raw_ptr);

      delete primitive_raw_ptr;
    }

    return primitives;
  }
  std::vector<rt3::Light* > API::make_lights(const std::vector<string> &light_type, const std::vector<ParamSet> &light_ps)
  {
    std::cout << ">>> Inside API::make_lights()\n";
    std::vector<rt3::Light* > lights;

    for (size_t i = 0; i < light_type.size(); ++i)
    {
      Light *light = nullptr;

      if (light_type[i] == "ambient")
      {
        light = create_ambient_light(light_ps[i]);
      }
      else if (light_type[i] == "directional")
      {
        // Extract the L, scale, from, and to values from the ParamSet and assign them to the light object's properties
        // ...
      }
      else if (light_type[i] == "point")
      {
        // Extract the I, scale, and from values from the ParamSet and assign them to the light object's properties
        // ...
      }
      else if (light_type[i] == "spot")
      {
        // Extract the I, scale, from, to, cutoff, and falloff values from the ParamSet and assign them to the light object's properties
        // ...
      }
      else
      {
        // Handle unknown light types (optional)
        // ...
      }

      lights.push_back(light);

    }

    return lights;
  }

  std::vector<rt3::Sphere> API::make_primitives_spheres(const std::vector<ParamSet> &object_ps, const std::vector<ParamSet> &object_material_ps)
  {
    std::cout << ">>> Inside API::make_primitives_sphere()\n";
    std::vector<rt3::Material *> materials;

    for (const auto &ps : object_material_ps)
    {
    std::cout << ">>> Inside API::create_material()\n";

      materials.push_back(create_material(ps));
    }

    std::vector<rt3::Sphere> primitives;
    for (size_t i = 0; i < object_ps.size(); ++i)
    {
      Sphere primitive_ptr = create_sphere(object_ps[i], materials[i]);

      primitives.emplace_back(primitive_ptr);
    }

    return primitives;
  }

  Camera *API::make_camera(const std::string &type, const ParamSet &camera_ps, const ParamSet &lookat_ps, Film *film)
  {
    std::cout << ">>> Inside API::make_camera()\n";
    Camera *cmr = nullptr;

    if (type == "orthographic")
    {
      cmr = create_orthographic_camera(camera_ps, lookat_ps, film);
    }
    else if (type == "perspective")
    {
      cmr = create_perspective_camera(camera_ps, lookat_ps, film);
    }
    else
    {
      RT3_ERROR("API::clean_up() called before engine initialization.");
    }

    return cmr;
  }

  Material *API::make_material(const std::string &name, const ParamSet &ps)
  {
    std::cout << ">>> Inside API::material()\n";
    Material *material{nullptr};
    material = create_material(ps);

    return material;
  }

  Scene *API::make_scene(Camera *camera, BackgroundColor *background, const std::vector<Sphere *> &primitives)
  {
    std::cout << ">>> Inside API::make_scene()\n";

    Scene *scene = new Scene(camera, std::move(background), primitives);

    return scene;
  }

  Integrator *API::make_integrator(const std::string &name, const ParamSet &ps, Camera *cam)
  {
    std::cout << ">>> Inside API::make_integrator()" << name << " s///\n";
    Integrator *itr = nullptr;

    if (name == "flat")
    {
      itr = create_sample_integrator(ps, cam);
    }
    else if (name == "depth_map")
    {
      itr = create_depth_integrator(ps, cam);
    }
    else if (name == "normal_map")
    {
      itr = create_normal_integrator(ps, cam);
    }
    else if (name == "blinn_phong_map")
    {
      itr = create_blinnphong_integrator(ps, cam);
    }
    else
    {
      RT3_ERROR("Unsupported integrator type.");
    }

    return itr;
  }

  void API::init_engine(const RunningOptions &opt)
  {

    curr_run_opt = opt;

    if (curr_state != APIState::Uninitialized)
    {
      RT3_ERROR("API::init_engine() has already been called! ");
    }

    curr_state = APIState::SetupBlock;

    render_opt = std::make_unique<RenderOptions>();

    RT3_MESSAGE("[1] Rendering engine initiated.\n");
  }

  void API::clean_up()
  {

    if (curr_state == APIState::Uninitialized)
    {
      RT3_ERROR("API::clean_up() called before engine initialization.");
    }
    else if (curr_state == APIState::WorldBlock)
    {
      RT3_ERROR("API::clean_up() called inside world definition section.");
    }
    curr_state = APIState::Uninitialized;

    RT3_MESSAGE("[4] Rendering engine clean up concluded. Shutting down...\n");
  }

  void API::run()
  {

    RT3_MESSAGE("[2] Beginning scene file parsing...\n");

    parse(curr_run_opt.filename.c_str());
  }

  void API::world_begin()
  {
    VERIFY_SETUP_BLOCK("API::world_begin");
    curr_state = APIState::WorldBlock;
  }

  void API::world_end()
  {
    VERIFY_WORLD_BLOCK("API::world_end");

    BackgroundColor *the_background{
        make_background(render_opt->bkg_type, render_opt->bkg_ps)};

    Film *the_film{
        make_film(render_opt->film_type, render_opt->film_ps)};

    Camera *cam = make_camera(render_opt->camera_type, render_opt->camera_ps, render_opt->lookat_ps, the_film);

    auto the_primitives = make_primitives_spheres(render_opt->object_ps, render_opt->object_material_ps);

    std::vector<Sphere *> primitive_pointers;
    for (auto &p : the_primitives)
    {
      primitive_pointers.push_back(&p);
    }

    Integrator *the_integrator{
        make_integrator(render_opt->integrator_type, render_opt->integrator_ps, cam)};

    Scene *scene_ptr = make_scene(cam, std::move(the_background), primitive_pointers);

    rt3::Scene scene(cam, std::move(the_background), primitive_pointers);

    if (the_film and the_background)
    {
      RT3_MESSAGE("    Parsing scene successfuly done!\n");
      RT3_MESSAGE("[2] Starting ray tracing progress.\n");

      auto res = the_film->get_resolution();
      size_t w = res[1];
      size_t h = res[0];
      RT3_MESSAGE("    Image dimensions in pixels (W x H): " + std::to_string(w) +
                  " x " + std::to_string(h) + ".\n");
      RT3_MESSAGE(
          "    Ray tracing is usually a slow process, please be patient: \n");

      auto start = std::chrono::steady_clock::now();

      the_integrator->render(scene);

      auto end = std::chrono::steady_clock::now();

      auto diff = end - start;

      auto diff_sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
      RT3_MESSAGE("    Time elapsed: " + std::to_string(diff_sec.count()) +
                  " seconds (" +
                  std::to_string(
                      std::chrono::duration<double, std::milli>(diff).count()) +
                  " ms) \n");
    }

    curr_state = APIState::SetupBlock;
    reset_engine();
  }

  void API::reset_engine()
  {

    render_opt = std::make_unique<RenderOptions>();
  }

  void API::background(const ParamSet &ps)
  {
    std::cout << ">>> Inside API::background()\n";
    VERIFY_WORLD_BLOCK("API::background");

    std::string type = retrieve(ps, "type", string{"unknown"});
    render_opt->bkg_type = type;

    render_opt->bkg_ps = ps;
  }

  void API::film(const ParamSet &ps)
  {
    std::cout << ">>> Inside API::film()\n";
    VERIFY_SETUP_BLOCK("API::film");

    std::string type = retrieve(ps, "type", string{"unknown"});
    render_opt->film_type = type;
    render_opt->film_ps = ps;
  }
// inicio estava assim
  void API::material(const ParamSet &ps)
  {
    std::cout << ">>> Inside API::material()\n";
    VERIFY_WORLD_BLOCK("API::material");

    std::string type = retrieve(ps, "type", string{"unknown"});
    render_opt->material_type = type;

    render_opt->material_ps = ps;
  }
//--------------------primeira tentativa

void API::create_named_material(const ParamSet &ps) {
  std::cout << ">>> Inside API::create_named_material()\n";
  VERIFY_WORLD_BLOCK("API::create_named_material");

  string material_name = retrieve(ps, "name", string());

  curr_GS.named_materials[material_name] = shared_ptr<Material>(create_material(ps));
}

// void API::material(const ParamSet &ps) {
//   std::cout << ">>> Inside API::material()\n";
//   VERIFY_WORLD_BLOCK("API::material");

//   shared_ptr<Material> new_material(create_material(ps));

//   curr_GS.curr_material = new_material;
// }

void API::named_material(const ParamSet &ps) {
  std::cout << ">>> Inside API::named_material()\n";
  VERIFY_WORLD_BLOCK("API::named_material");

  string material_name = retrieve(ps, "name", string());
  curr_GS.named_materials[material_name];
}

  void API::object(const ParamSet &ps)
  {
    std::cout << ">>> Inside API::object()\n";
    VERIFY_WORLD_BLOCK("API::object");

    std::string type = retrieve(ps, "type", string{"unknown"});
    render_opt->object_type = type;
    render_opt->object_ps.push_back(ps);
    render_opt->object_material_ps.push_back(render_opt->material_ps);
  }

  void API::light(const ParamSet &ps)
  {
    std::cout << ">>> Inside API::light()\n";
    VERIFY_WORLD_BLOCK("API::light");

    std::string type = retrieve(ps, "type", string{"unknown"});
    render_opt->light_type.push_back(type);
    render_opt->light_ps.push_back(ps);
  }

  void API::camera(const ParamSet &ps)
  {
    std::cout << ">>> Inside API::camera()\n";
    VERIFY_SETUP_BLOCK("API::camera");

    std::string type = retrieve(ps, "type", string{"unknown"});
    render_opt->camera_type = type;

    render_opt->camera_ps = ps;
  }

  void API::look_at(const ParamSet &ps)
  {
    std::cout << ">>> Inside API::look_at()\n";
    VERIFY_SETUP_BLOCK("API::look_at");

    std::string type = retrieve(ps, "type", string{"unknown"});
    render_opt->lookat_ps = ps;
  }

  void API::integrator(const ParamSet &ps)
  {
    std::cout << ">>> Inside API::integrator()\n";
    VERIFY_SETUP_BLOCK("API::integrator");

    std::string type = retrieve(ps, "type", string{"unknown"});
    std::cout << ">>> Inside API::integrator()\n"
              << type;

    render_opt->integrator_type = type;
    render_opt->integrator_ps = ps;
  }

  void API::scene(const ParamSet &ps)
  {
    std::cout << ">>> Inside API::scene()\n";
    VERIFY_SETUP_BLOCK("API::scene");

    std::string type = retrieve(ps, "type", string{"unknown"});
    render_opt->scene_type = type;
    render_opt->scene_ps = ps;
  }
}