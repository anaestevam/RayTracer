#include "api.h"
#include "background.h"
#include "scene.h"
#include "sphere.h"
#include "paramset.h"
#include "ray.h"
#include "samplerintegrator.h"
#include "depthintegrator.h"
#include "normalintegrator.h"

#include <chrono>
#include <memory>

namespace rt3
{

  //=== API's static members declaration and initialization.
  API::APIState API::curr_state = APIState::Uninitialized;
  RunningOptions API::curr_run_opt;
  std::unique_ptr<RenderOptions> API::render_opt;
  // GraphicsState API::curr_GS; // criar ponteiro pro material e a bibliotera de materiais <DictionaryOfMaterial>

  // THESE FUNCTIONS ARE NEEDED ONLY IN THIS SOURCE FILE (NO HEADER NECESSARY)
  // ˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇ

  Film *API::make_film(const std::string &name, const ParamSet &ps)
  {
    std::cout << ">>> Inside API::make_film()\n";
    Film *film{nullptr};
    film = create_film(ps);

    // Return the newly created film.
    return film;
  }

  BackgroundColor *API::make_background(const std::string &name, const ParamSet &ps)
  {
    std::cout << ">>> Inside API::background()\n";
    BackgroundColor *bkg{nullptr};
    bkg = create_color_background(ps, new BackgroundColor());
    // Return the newly created background.
    return bkg;
  }

  std::vector<rt3::Primitive> API::make_primitives(const std::vector<ParamSet> &object_ps, const std::vector<ParamSet> &object_material_ps)
  {
    std::cout << ">>> Inside API::make_primitives()\n";
    std::vector<rt3::Material *> materials;

    for (const auto &ps : object_material_ps)
    {
      // Create a Material object from the ParamSet and add it to the materials vector
      materials.push_back(create_material(ps));
    }

    std::vector<rt3::Primitive> primitives;
    for (size_t i = 0; i < object_ps.size(); ++i)
    {
      std::unique_ptr<rt3::Primitive> primitive_ptr = create_primitive(object_ps[i], materials[i]);

      // Move the unique pointer into a local variable
      rt3::Primitive *primitive_raw_ptr = primitive_ptr.release();

      // Add the primitive to the vector
      primitives.emplace_back(*primitive_raw_ptr);

      // Release ownership of the raw pointer
      delete primitive_raw_ptr;
    }

    return primitives;
  }

  std::vector<rt3::Sphere> API::make_primitives_spheres(const std::vector<ParamSet> &object_ps, const std::vector<ParamSet> &object_material_ps)
  {
    std::cout << ">>> Inside API::make_primitives_sphere()\n";
    std::vector<rt3::Material *> materials;

    for (const auto &ps : object_material_ps)
    {
      // Create a Material object from the ParamSet and add it to the materials vector
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

    // Return the newly created camera.
    return cmr;
  }

  Material *API::make_material(const std::string &name, const ParamSet &ps)
  {
    std::cout << ">>> Inside API::material()\n";
    Material *material{nullptr};
    material = create_material(ps);
    // Return the newly created background.
    //acrescentar condicao pro tipo flag, blinn
    //curr_material
    return material;
  }
/*make_named_material vou buscar o curr na biblioteca e faz o hash table 
procurar o material no rash table e jogar pro make_material
named_material só busca com o find e mostra o erro com o end, crr_GS.curr_material = it->second*/
  Scene *API::make_scene(Camera *camera, BackgroundColor *background, const std::vector<Sphere *> &primitives)
  {
    std::cout << ">>> Inside API::make_scene()\n";

    // Create the Scene object with the provided camera, background, and primitives
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
    // else if (name == "depth_map")
    // {
    //   itr = create_depth_integrator(ps, cam);
    // }
    else if (name == "normal_map")
    {
      itr = create_normal_integrator(ps, cam);
    }
    else
    {
      RT3_ERROR("Unsupported integrator type.");
    }

    return itr;
  }

  // ˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆ
  // END OF THE AUXILIARY FUNCTIONS
  // =========================================================================

  //=== API's public methods implementation
  void API::init_engine(const RunningOptions &opt)
  {
    // Save running option sent from the main().
    curr_run_opt = opt;
    // Check current machine state.
    if (curr_state != APIState::Uninitialized)
    {
      RT3_ERROR("API::init_engine() has already been called! ");
    }
    // Set proper machine state
    curr_state = APIState::SetupBlock;
    // Preprare render infrastructure for a new scene.
    render_opt = std::make_unique<RenderOptions>();
    // Create a new initial GS
    // curr_GS = GraphicsState(); // criar
    RT3_MESSAGE("[1] Rendering engine initiated.\n");
  }

  void API::clean_up()
  {
    // Check for correct machine state
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
    // Try to load and parse the scene from a file.
    RT3_MESSAGE("[2] Beginning scene file parsing...\n");
    // Recall that the file name comes from the running option struct.
    parse(curr_run_opt.filename.c_str());
  }

  void API::world_begin()
  {
    VERIFY_SETUP_BLOCK("API::world_begin"); // check for correct machine state.
    curr_state = APIState::WorldBlock;      // correct machine state.
  }

  void API::world_end()
  {
    VERIFY_WORLD_BLOCK("API::world_end");
    // The scene has been properly set up and the scene has
    // already been parsed. It's time to render the scene.

    // At this point, we have the background as a solitary pointer here.
    // In the future, the background will be parte of the scene object.
    BackgroundColor *the_background{
        make_background(render_opt->bkg_type, render_opt->bkg_ps)};
    // Same with the film, that later on will belong to a camera object.
    Film *the_film{
        make_film(render_opt->film_type, render_opt->film_ps)};

    Camera *cam = make_camera(render_opt->camera_type, render_opt->camera_ps, render_opt->lookat_ps, the_film);
    // auto the_primitives  = make_primitives(render_opt->object_ps, render_opt->object_material_ps);
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

    //  the_integrator.reset( make_integrator() ); // make Film, make Camera.
    //   // [2] Create the scene.
    //   the_scene.reset( make_scene() ); // make Primitives, make Background.

    // Run only if we got film and background.
    if (the_film and the_background)
    {
      RT3_MESSAGE("    Parsing scene successfuly done!\n");
      RT3_MESSAGE("[2] Starting ray tracing progress.\n");

      // Structure biding, c++17.
      auto res = the_film->get_resolution();
      size_t w = res[0];
      size_t h = res[1];
      RT3_MESSAGE("    Image dimensions in pixels (W x H): " + std::to_string(w) +
                  " x " + std::to_string(h) + ".\n");
      RT3_MESSAGE(
          "    Ray tracing is usually a slow process, please be patient: \n");

      //================================================================================
      auto start = std::chrono::steady_clock::now();

      the_integrator->render(scene); // Main ray tracer loop!!!

      auto end = std::chrono::steady_clock::now();
      //================================================================================
      auto diff = end - start; // Store the time difference between start and end
      // Seconds
      auto diff_sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
      RT3_MESSAGE("    Time elapsed: " + std::to_string(diff_sec.count()) +
                  " seconds (" +
                  std::to_string(
                      std::chrono::duration<double, std::milli>(diff).count()) +
                  " ms) \n");
    }
    // [4] Basic clean up
    curr_state = APIState::SetupBlock; // correct machine state.
    reset_engine();
  }

  /// This api function is called when we need to re-render the *same* scene (i.e.
  /// objects, lights, materials, etc) , maybe with different integrator, and
  /// camera setup. Hard reset on the engine. User needs to setup all entities,
  /// such as camera, integrator, accelerator, etc.
  void API::reset_engine()
  {
    // curr_GS = GraphicsState();
    // This will delete all information on integrator, cameras, filters,
    // acceleration structures, etc., that has been set previously.
    render_opt = std::make_unique<RenderOptions>();
  }

  void API::background(const ParamSet &ps)
  {
    std::cout << ">>> Inside API::background()\n";
    VERIFY_WORLD_BLOCK("API::background");

    // retrieve type from ps.
    std::string type = retrieve(ps, "type", string{"unknown"});
    render_opt->bkg_type = type;
    // Store current background object.
    render_opt->bkg_ps = ps;
  }

  void API::film(const ParamSet &ps)
  {
    std::cout << ">>> Inside API::film()\n";
    VERIFY_SETUP_BLOCK("API::film");

    // retrieve type from ps.
    std::string type = retrieve(ps, "type", string{"unknown"});
    render_opt->film_type = type;
    render_opt->film_ps = ps;
  }

  void API::material(const ParamSet &ps)
  {
    std::cout << ">>> Inside API::material()\n";
    VERIFY_WORLD_BLOCK("API::material");

    // retrieve type from ps.
    std::string type = retrieve(ps, "type", string{"unknown"});
    render_opt->material_type = type;
    // Store current background object.
    render_opt->material_ps = ps;
  }

  void API::object(const ParamSet &ps)
  {
    std::cout << ">>> Inside API::object()\n";
    VERIFY_WORLD_BLOCK("API::object");

    // retrieve type from ps.
    std::string type = retrieve(ps, "type", string{"unknown"});
    render_opt->object_type = type;
    render_opt->object_ps.push_back(ps);
    render_opt->object_material_ps.push_back(render_opt->material_ps);
  }

  void API::camera(const ParamSet &ps)
  {
    std::cout << ">>> Inside API::camera()\n";
    VERIFY_SETUP_BLOCK("API::camera");

    // retrieve type from ps.
    std::string type = retrieve(ps, "type", string{"unknown"});
    render_opt->camera_type = type;
    // Store current camera object.

    render_opt->camera_ps = ps;
  }

  void API::look_at(const ParamSet &ps)
  {
    std::cout << ">>> Inside API::look_at()\n";
    VERIFY_SETUP_BLOCK("API::look_at");
    // retrieve type from ps.
    std::string type = retrieve(ps, "type", string{"unknown"});
    render_opt->lookat_ps = ps;
  }

  void API::integrator(const ParamSet &ps)
  {
    std::cout << ">>> Inside API::integrator()\n";
    VERIFY_SETUP_BLOCK("API::integrator");
    // retrieve type from ps.
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
    // retrieve type from ps.
    std::string type = retrieve(ps, "type", string{"unknown"});
    render_opt->scene_type = type;
    render_opt->scene_ps = ps;
  }
} // namespace rt3
