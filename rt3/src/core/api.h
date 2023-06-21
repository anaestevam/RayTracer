#ifndef API_H
#define API_H 1

#include <string>

#include "rt3.h"
#include "paramset.h"
#include "integrator/samplerintegrator.h"
#include "integrator/depthintegrator.h"
#include "integrator/normalintegrator.h"

#define VERIFY_INITIALIZED(func_name)                                                                                     \
  if (curr_state == APIState::Uninitialized)                                                                              \
  {                                                                                                                       \
    RT3_ERROR(std::string{"API::init() must be called before "} + std::string{func_name} + std::string{"(). Ignoring."}); \
  }

#define VERIFY_SETUP_BLOCK(func_name)                                                                                                                                             \
  VERIFY_INITIALIZED(func_name)                                                                                                                                                   \
  if (curr_state == APIState::WorldBlock)                                                                                                                                         \
  {                                                                                                                                                                               \
    RT3_ERROR(std::string{"Rendering setup cannot happen inside "} + std::string{"World definition block; "} + std::string{func_name} + std::string{"() not allowed. Ignoring"}); \
  }

#define VERIFY_WORLD_BLOCK(func_name)                                                                                                                                             \
  VERIFY_INITIALIZED(func_name)                                                                                                                                                   \
  if (curr_state == APIState::SetupBlock)                                                                                                                                         \
  {                                                                                                                                                                               \
    RT3_ERROR(std::string{"Scene description must happen inside "} + std::string{"World Definition block; "} + std::string{func_name} + std::string{"() not allowed. Ignoring"}); \
  }

namespace rt3
{

  struct RenderOptions
  {
    std::string material_type{"flat"};  
    ParamSet material_ps;

    std::string object_type{"sphere"};  
    std::vector<ParamSet> object_ps;
    std::vector<ParamSet> object_material_ps;

    std::vector<std::string> light_type{"ambient"}; 
    std::vector<ParamSet> light_ps;

    std::string integrator_type{"flat"};  

    ParamSet integrator_ps;
    std::string scene_type{"sample"};  
    ParamSet scene_ps;

    std::string film_type{"image"};  
    ParamSet film_ps;

    string camera_type{"perspective"};
    ParamSet camera_ps;
    ParamSet lookat_ps;

    string bkg_type{"solid"}; 
    ParamSet bkg_ps;
  };

  struct GraphicsState
  {
    // Not necessary in Project 01 through Project 07. tem um ponteiro pro material.
      std::shared_ptr<Material> curr_material;  //!< Current material that globally affects all objects.
	    //bool flip_normals{false};              //!< When true, we flip the normals
	    std::map<std::string, std::shared_ptr<Material>> named_materials;      //!< Library of materials.
	    //bool mats_lib_cloned{false};  
  };

  class API
  {
  public:

    enum class APIState
    {
      Uninitialized, 
      SetupBlock,    
      WorldBlock
    }; 

    static RunningOptions curr_run_opt;

    static std::unique_ptr<RenderOptions> render_opt;

    static GraphicsState curr_GS;

  private:

    static APIState curr_state;

    static Film *make_film(const string &name, const ParamSet &ps);
    static BackgroundColor *make_background(const string &name, const ParamSet &ps);
    static Camera* make_camera(const std::string& type, const ParamSet& camera_ps, const ParamSet& lookat_ps, Film* film);
    static Material *make_material(const std::string& name, const ParamSet &ps);
    static std::vector<rt3::Primitive> make_primitives(const std::vector<ParamSet>& object_ps, const std::vector<ParamSet>& object_material_ps);
    static std::vector<rt3::Sphere> make_primitives_spheres(const std::vector<ParamSet>& object_ps, const std::vector<ParamSet>& object_material_ps);
    static std::vector<rt3::Light *> make_lights(const std::vector<string>& light_type, const std::vector<ParamSet>& light_ps);
    static Integrator* make_integrator(const std::string &name, const ParamSet &ps,rt3::Camera* cam );
    static Scene* make_scene(Camera* camera, BackgroundColor* background, const std::vector<Sphere*>& primitives);

  public:
    static std::unique_ptr<Film> the_film;
    static std::unique_ptr<Background> the_background;

    static void init_engine(const RunningOptions &);
    static void run();
    static void clean_up();
    static void reset_engine();

    static void film(const ParamSet &ps);
    static void camera(const ParamSet &ps);
    static void look_at(const ParamSet& ps);
    static void material(const ParamSet &ps);
    static void create_named_material( const ParamSet& ps );
	  static void named_material(const ParamSet& ps);
    static void object(const ParamSet &ps);
    static void background(const ParamSet &ps);
    static void integrator(const ParamSet &ps);
    static void light(const ParamSet &ps);
    static void scene(const ParamSet &ps);
    static void world_begin();
    static void world_end();
  };
} 

#endif 