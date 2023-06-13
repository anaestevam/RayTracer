// #include "depthintegrator.h"


// namespace rt3
// {
// void DepthIntegrator::render(const Scene &scene)
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

// ColorXYZ interpolate(const ColorXYZ &color1, const ColorXYZ &color2, float fraction)
// {
//     ColorXYZ result;

//     result[0] = color1[0] * (1.0f - fraction) + color2[0] * fraction;
//     result[1] = color1[1] * (1.0f - fraction) + color2[1] * fraction;
//     result[2] = color1[2] * (1.0f - fraction) + color2[2] * fraction;

//     return result;
// }


// float sphere_distance(const Point3f &point, const Point3f &center, float radius)
// {
//     float x = point[0] - center[0];
//     float y = point[1] - center[1];
//     float z = point[2] - center[2];

//     float distance_squared = x * x + y * y + z * z;
//     float radius_squared = radius * radius;

//     return sqrt(distance_squared - radius_squared);
// }


// ColorXYZ DepthIntegrator::Li(const Ray &ray, const Scene &scene,const Point2f &pixel_coords)
//   {
//     ColorXYZ color{0, 0, 0};


//       if (scene.backgroundColor->mapping_type == Background::mapping_t::screen)
//         color = scene.backgroundColor->sampleXYZ(pixel_coords);
//       else if (scene.backgroundColor->mapping_type == Background::mapping_t::spherical)
//         color = scene.backgroundColor->sampleXYZ(pixel_coords);
    
//     for (const auto &p : scene.primitives)
//     {
   
//           float normalized_depth_value = calculate_normalized_depth(ray, scene, pixel_coords, zmin, zmax);
//          color = interpolate(far_color,  near_color, normalized_depth_value);
    
//     }



//     return color;
//   }

// float calculate_normalized_depth(const Ray &ray, const Scene &scene, const Point2f &pixel_coords, float min_z , float max_z)
// {
//     float depth = 0.0f;
//     bool is_intersecting = false;

//     for (const auto &p : scene.primitives)
//     {
//         Sphere *sphere = dynamic_cast<Sphere *>(p);
//         if (sphere != nullptr)
//         {
//             is_intersecting = sphere->intersect_p(ray);
//             if (is_intersecting)
//             {
//                 Point3f sphere_center = sphere->center;
//                 depth = sphere_distance(ray.o, sphere_center, sphere->radius);
//                 break;
//             }
//         }
//     }

//     if (is_intersecting)
//     {
//         return (depth - min_z) / (max_z - min_z);
//     }

//     return 0.0f;
// }



// DepthIntegrator* create_depth_integrator(const ParamSet &ps, Camera* cam) 
//   {
//         float zmin = retrieve(ps, "zmin", 0.f);
//         float zmax = retrieve(ps,"zmax", 1.f);
//         ColorXYZ near_color =retrieve(ps,"near_color", ColorXYZ{0, 0, 0});
//         ColorXYZ far_color = retrieve(ps,"far_color", ColorXYZ{1, 1, 1});
//         return new DepthIntegrator(cam, zmin, zmax, near_color, far_color);
//   }

// }
