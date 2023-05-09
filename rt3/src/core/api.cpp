#include "api.h"
#include "background.h"
#include "scene.h"

#include <chrono>
#include <memory>

namespace rt3
{

  // void render(rt3::Film the_film, rt3::BackgroundColor the_background)
  // {
  //   // Get film resolution
  //   auto res = the_film.get_resolution();
  //   size_t w = res[0];
  //   size_t h = res[1];

  //   // Iterate through each pixel of the image
  //   for (size_t y = 0; y < h; ++y)
  //   {
  //     for (size_t x = 0; x < w; ++x)
  //     {
  //       // Compute the normalized coordinates of the current pixel
  //       Point2f pixel_coords{static_cast<float>(x), static_cast<float>(y)};

  //       // Cast a ray into the scene and compute the resulting color
  //       ColorXYZ color = the_background.sampleXYZ(pixel_coords);

  //       // Add the computed color as a sample to the film object
  //       the_film.add_sample(pixel_coords, color);
  //     }
  //   }

  //   the_film.write_image(w, h, 1, the_film.m_filename);
  // }

  void render(const std::shared_ptr<Scene> &s)
  {
    auto res = s->camera->film.get_resolution();
    size_t w = res[0];
    size_t h = res[1];
    for (size_t y = 0; y < h; ++y)
    {
      for (size_t x = 0; x < w; ++x)
      {
        Ray ray = s->camera->generate_ray(x, y);
        Point2f pixel_coords{static_cast<float>(x), static_cast<float>(y)};
        ColorXYZ color{0, 0, 0};
        if (s->backgroundColor->mapping_type == Background::mapping_t::screen)
          color = s->backgroundColor->sampleXYZ(pixel_coords);
        else if (s->backgroundColor->mapping_type == Background::mapping_t::spherical)
          color = s->backgroundColor->sampleXYZ(pixel_coords);
        // ...
        // for (const auto &p : s->obj_list)
        // {
        //   // ...
        // }
        s->camera->film.add_sample(pixel_coords, color);
      }
    }
    s->camera->film.write_image(w, h, 1, s->camera->film.m_filename);
  }

  //=== API's static members declaration and initialization.
  API::APIState API::curr_state = APIState::Uninitialized;
  RunningOptions API::curr_run_opt;
  std::unique_ptr<RenderOptions> API::render_opt;
  // GraphicsState API::curr_GS;

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
    // curr_GS = GraphicsState();
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
    std::unique_ptr<BackgroundColor> the_background{
        make_background(render_opt->bkg_type, render_opt->bkg_ps)};
    // Same with the film, that later on will belong to a camera object.
    std::unique_ptr<Film> the_film{
        make_film(render_opt->film_type, render_opt->film_ps)};

    std::shared_ptr<Camera> cam = std::make_shared<Camera>(*the_film);
    std::vector<std::shared_ptr<Primitive>> obj_list;
    std::shared_ptr<Scene> scene = std::make_shared<Scene>(*cam, *the_background, obj_list);

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
      // render(*the_film, *the_background);

      render(scene);

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

} // namespace rt3