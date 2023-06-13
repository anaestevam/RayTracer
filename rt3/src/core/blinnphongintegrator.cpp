// #include "blinnphongintegrator.h"


// namespace rt3
// {
//   void BlinnPhongIntegrator::render(const Scene &scene)
//   {
//     auto res = camera->film->get_resolution();
//     size_t w = res[0];
//     size_t h = res[1];

//     for (size_t y = 0; y < h; ++y)
//     {
//       for (size_t x = 0; x < w; ++x)
//       {
//         Ray r = camera->generate_ray(x, y);
//         Point2f pixel_coords{static_cast<float>(x) / static_cast<float>(w), static_cast<float>(y) / static_cast<float>(h)};
//         ColorXYZ color = Li(r, scene, pixel_coords);

//         camera->film->add_sample(pixel_coords, color);
//       }
//     }
//     camera->film->write_image(w, h, 1, camera->film->m_filename);
//   }

//   ColorXYZ BlinnPhongIntegrator::Li(const Ray &ray, const Scene &scene,const Point2f &pixel_coords)
//   {
//     ColorXYZ color{0, 0, 0};


//       if (scene.backgroundColor->mapping_type == Background::mapping_t::screen)
//         color = scene.backgroundColor->sampleXYZ(pixel_coords);
//       else if (scene.backgroundColor->mapping_type == Background::mapping_t::spherical)
//         color = scene.backgroundColor->sampleXYZ(pixel_coords);
//       for (const auto &p : scene.primitives) {
//               bool is_intersecting = false;

//       Sphere *sphere = dynamic_cast<Sphere *>(p);
//       if (sphere != nullptr)
//       {
//         is_intersecting = sphere->intersect_p(ray);
//       }

//       if (is_intersecting)
//             Sphere *sphere = dynamic_cast<Sphere *>(p);
//             if (sphere != nullptr) {
//                 ColorXYZ L = sphere->material->color;
//                 float atten = CalcAttenuation(ray.cameraSpacePosition, lightDir);
//                 Vector4f attenIntensity = atten * lightIntensity;

//                 Vector3f surfaceNormal = vertexNormal.normalized();
//                 float cosAngIncidence = surfaceNormal.dot(lightDir);
//                 cosAngIncidence = clamp(cosAngIncidence, 0, 1);
//                 cosAngIncidence = cosAngIncidence != 0.0 ? cosAngIncidence : 0.0;

//                 Vector3f halfVector = normalize(lightDir + viewDirection);
//                 float blinnTerm = dot(surfaceNormal, halfVector);
//                 blinnTerm = clamp(blinnTerm, 0, 1);
//                 blinnTerm = cosAngIncidence != 0.0 ? blinnTerm : 0.0;

//                 color = (diffuseColorXYZ * attenIntensity * cosAngIncidence) +
//                       (specularColorXYZ * attenIntensity * blinnTerm) +
//                       (diffuseColorXYZ * ambientIntensity);
//             }
//         }
//     }
//     return color;
//   }

//   BlinnPhongIntegrator* create_blinnphong_integrator(const ParamSet &ps, Camera* cam) 
//   {
//     return new BlinnPhongIntegrator(cam);
//   }
// }