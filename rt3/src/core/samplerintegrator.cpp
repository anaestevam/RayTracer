#include "samplerintegrator.h"
#include "rt3.h"
#include "paramset.h"
#include "ray.h"

namespace rt3
{
  void SamplerIntegrator::render(const Scene &scene)
  {
    auto res = camera->film->get_resolution();
    size_t w = res[0];
    size_t h = res[1];

    for (size_t y = 0; y < h; ++y)
    {
      for (size_t x = 0; x < w; ++x)
      {
        Ray r = camera->generate_ray(x, y);
        Point2f pixel_coords{static_cast<float>(x) / static_cast<float>(w), static_cast<float>(y) / static_cast<float>(h)};
        ColorXYZ color = Li(r, scene);

        camera->film->add_sample(pixel_coords, color);
      }
    }
    camera->film->write_image(w, h, 1, camera->film->m_filename);
  }

  ColorXYZ SamplerIntegrator::Li(const Ray &ray, const Scene &scene)
  {
    ColorXYZ color{0, 0, 0};

    for (const auto &p : scene.primitives)
    {
      bool is_intersecting = false;

      Sphere *sphere = dynamic_cast<Sphere *>(p);
      if (sphere != nullptr)
      {
        is_intersecting = sphere->intersect_p(ray);
      }

      if (is_intersecting)
      {
        color = sphere->material->color;
      }
    }

    if (color == ColorXYZ{0, 0, 0})
    {
      Point2f pixel_coords{0.5f, 0.5f};
      if (scene.backgroundColor->mapping_type == Background::mapping_t::screen)
        color = scene.backgroundColor->sampleXYZ(pixel_coords);
      else if (scene.backgroundColor->mapping_type == Background::mapping_t::spherical)
        color = scene.backgroundColor->sampleXYZ(pixel_coords);
    }

    return color;
  }

  SamplerIntegrator* create_sample_integrator(const ParamSet &ps, Camera* cam) 
  {
    return new SamplerIntegrator(cam);
  }
}