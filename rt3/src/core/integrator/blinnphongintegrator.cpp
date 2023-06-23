#include "blinnphongintegrator.h"

namespace rt3
{
  void BlinnPhongIntegrator::render(const Scene &scene)
  {
    auto res = camera->film->get_resolution();
    size_t w = res[0];
    size_t h = res[1];
      for (size_t x = 0; x < w; ++x)

    {
          for (size_t y = 0; y < h; ++y)

      {
        Ray r = camera->generate_ray(x, y);
        Point2f pixel_coords{static_cast<float>(x) / static_cast<float>(w), static_cast<float>(y) / static_cast<float>(h)};
        ColorXYZ color = Li(r, scene, pixel_coords);

        camera->film->add_sample(pixel_coords, color);
      }
    }
    camera->film->write_image(w, h, 1, camera->film->m_filename);
  }

  ColorXYZ BlinnPhongIntegrator::Li(const Ray &ray, const Scene &scene, const Point2f &pixel_coords)
  {
    ColorXYZ color{0, 0, 0};
    auto res = camera->film->get_resolution();
    size_t w = res[0];
    size_t h = res[1];
    ColorXYZ L{0, 0, 0}; // The radiance

    for (const auto &p : scene.primitives)
    {

      SurfaceInteraction isect;
      if (!scene.intersect(ray, &isect))
      {

        if (scene.backgroundColor->mapping_type == Background::mapping_t::screen)
          color = scene.backgroundColor->sampleXYZ(pixel_coords);
        else if (scene.backgroundColor->mapping_type == Background::mapping_t::spherical)
          color = scene.backgroundColor->sampleXYZ(pixel_coords);
      }
      else
      {


        Point3f KaIa = Point3f(0.0, 0.0, 0.0);
        Vector3f wi;
        VisibilityTester vt;

        Material *material = isect.m;
        BlinnMaterial *fm = dynamic_cast<BlinnMaterial *>(material);

        if (fm != nullptr)
        {
          
          auto ka = fm->get_ka();
          auto kd = fm->get_kd();
          auto ks = fm->get_ks();
          auto gloss = fm->get_ge();

          for (auto l : scene.lights)
          {
            l->set_bounding_box(this->bounding_box_world);

            if (l->is_ambient())
            {
              KaIa = ka * l->get_intensity();
            }
            else
            {
              auto Ii = l->Li(isect, &wi, &vt);
              auto n = isect.n;

              auto wo = isect.wo;
              auto h = wo + wi;
              h.make_unit_vector();

              if (vt.unoccluded(scene))
              {
                std::cout << ">>> Inside API::make_camera()\n"<< L;

                Point3f aaa = (ks * Ii * pow(fmax(0.0, n.dot(h)), gloss)) + (kd * Ii * fmax(0.0, n.dot(wi)));
                L[0] = L[0] + aaa[0];
                L[1] = L[1] + aaa[1];
                L[2] = L[2] + aaa[2];
              }
            }
          }

          L[0] = (L[0] + KaIa[0]);
          L[1] = (L[1] + KaIa[1])* 255.0f;
          L[2] = (L[2] + KaIa[2])* 255.0f;

          color = L;
           }
        else
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
      }
    }

    return color;
  }


  BlinnPhongIntegrator *create_blinnphong_integrator(const ParamSet &ps, Camera *cam)
  {
    return new BlinnPhongIntegrator(cam);
  }
}