#include "blinnphongintegrator.h"

namespace rt3
{
  void BlinnPhongIntegrator::render(const Scene &scene)
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
        ColorXYZ color = Li(r, scene, pixel_coords, 10);

        camera->film->add_sample(pixel_coords, color);
      }
    }
    camera->film->write_image(w, h, 1, camera->film->m_filename);
  }

  ColorXYZ BlinnPhongIntegrator::Li(const Ray &ray, const Scene &scene, const Point2f &pixel_coords, int depth)
  {
    ColorXYZ color{0, 0, 0};
    auto res = camera->film->get_resolution();
    size_t w = res[0];
    size_t h = res[1];
    ColorXYZ L{0, 0, 0}; // The radiance
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
      return L;

    for (const auto &p : scene.primitives)
    {

      SurfaceInteraction isect;
      if (!scene.intersect(ray, &isect))
      {

        if (scene.backgroundColor->mapping_type == Background::mapping_t::screen)
          color = scene.backgroundColor->sampleXYZ(pixel_coords);
        else if (scene.backgroundColor->mapping_type == Background::mapping_t::spherical)
          color = scene.backgroundColor->sampleXYZ(pixel_coords);
        return color;
      }
      else
      {
        // Point3f normal = (isect.p - p->center) / p->radius;
        // Point3f target = isect.p + normal + isect.n.random_unit_vector();
        // L =  Li(Ray(isect.p, isect.n.ToVector3(target - isect.p)), scene, pixel_coords, depth-1);
        // L[0] = (L[0] * 0.5);
        // L[1] = (L[1] * 0.5);
        // L[2] = (L[2] * 0.5);

        // return color;

        Ray scattered;
        ColorXYZ attenuation;
        if (isect.m->emitted(ray, isect, attenuation, scattered))
        {
          L = Li(scattered, scene, pixel_coords, depth - 1);
          std::cout << ">>> " << L[0] <<"/n";

          L[0] = L[0] * attenuation[0];
          L[1] = L[1] * attenuation[1];
          L[2] = L[2] * attenuation[2];
          return L;
        }
        return ColorXYZ{0, 0, 0};
      }

      // Point3f KaIa = Point3f(0.0, 0.0, 0.0);
      // Vector3f wi;
      // VisibilityTester vt;

      // Material *material = isect.m;
      // BlinnMaterial *fm = dynamic_cast<BlinnMaterial *>(material);

      // if (fm != nullptr)
      // {

      //   auto ka = fm->get_ka();
      //   auto kd = fm->get_kd();
      //   auto ks = fm->get_ks();
      //   auto gloss = fm->get_ge();

      //   for (auto l : scene.lights)
      //   {
      //     l->set_bounding_box(this->bounding_box_world);

      //     if (l->is_ambient())
      //     {
      //       KaIa = ka * l->get_intensity();
      //     }
      //     else
      //     {
      //       auto Ii = l->Li(isect, &wi, &vt);
      //       auto n = isect.n;

      //       auto wo = isect.wo;
      //       auto h = wo + wi;
      //       h.make_unit_vector();

      //       if (vt.unoccluded(scene))
      //       {
      //         std::cout << ">>> Inside API::make_camera()\n"
      //                   << L;

      //         Point3f aaa = (ks * Ii * pow(fmax(0.0, n.dot(h)), gloss)) + (kd * Ii * fmax(0.0, n.dot(wi)));
      //         L[0] = L[0] + aaa[0];
      //         L[1] = L[1] + aaa[1];
      //         L[2] = L[2] + aaa[2];
      //       }
      //     }
      //   }

      //   L[0] = (L[0] + KaIa[0]);
      //   L[1] = (L[1] + KaIa[1]) * 255.0f;
      //   L[2] = (L[2] + KaIa[2]) * 255.0f;

      // color = L;
      // }
      // else
      // {

      //   bool is_intersecting = false;

      //   Sphere *sphere = dynamic_cast<Sphere *>(p);
      //   if (sphere != nullptr)
      //   {
      //     is_intersecting = sphere->intersect_p(ray);
      //   }

      //   if (is_intersecting)
      //   {
      //     color = sphere->material->color;
      //   }
      //}
      //}
    }

    //  auto scale = 1 / 2;

    //             //  std::cout << ">>> " << color[0] <<scale * color[0]  <<  "\n";

    //  color[0]  = sqrt( color[0] );
    //   color[1]  = sqrt(color[1] );
    //   color[2]  = sqrt( color[2] );
    //      // Clamp the color values to [0, 1].
    //           // std::cout << ">>> " << color[0] << "/n";

    //   color[0] = clamp(color[0], 0.0, 0.999) * 255;
    //   color[1] = clamp(color[1], 0.0,  0.999) * 255;
    //   color[2] = clamp(color[2], 0.0,  0.999) * 255;
    //   //  std::cout << ">>> " << color[0] <<"/n";

    return color;
  }

  inline double clamp(double x, double min, double max)
  {
    if (x < min)
      return min;
    if (x > max)
      return max;
    return x;
  }

  BlinnPhongIntegrator *create_blinnphong_integrator(const ParamSet &ps, Camera *cam)
  {
    return new BlinnPhongIntegrator(cam);
  }

}