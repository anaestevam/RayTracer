// #ifndef LIGHT_H
// #define LIGHT_H

// #include "scene.h"
// #include "rt3.h"
// #include "paramset.h"
// namespace rt3
// {
// enum class light_flag_e : int {
//   point = 1,
//   directional = 2,
//   area = 4,
//   ambient = 8,
//   spot = 16,
//   positional = 32,
// };

// class Surfel {
// public:
//   Vector3f p;
//   Vector3f n;
//   Vector3f dpdu;
//   Vector3f dpdv;
//   float u;
//   float v;

//   Surfel() {}
//   Surfel(const Vector3f& p, const Vector3f& n, const Vector3f& dpdu, const Vector3f& dpdv, float u, float v)
//       : p(p), n(n.normalized()), dpdu(dpdu), dpdv(dpdv), u(u), v(v) {}
// };


// class SurfaceInteraction {
// public:
//   float t;
//   Surfel surfel;
//   Material* material;

//   SurfaceInteraction() : t(std::numeric_limits<float>::infinity()), material(nullptr) {}
//   SurfaceInteraction(const Surfel& surfel, float t, Material* material) : surfel(surfel), t(t), material(material) {}

//   Vector3f wo() const {
//     return -ray.d;
//   }

//   Vector3f wi(const Vector3f& w) const {
//     return (2.0f * surfel.n.dot(w) * surfel.n - w).normalized();
//   }

//   ColorXYZ Le(const Vector3f& dir) const {
//     if (material) {
//       return material->emitted(ray, surfel, dir);
//     }
//     return ColorXYZ{0.0,0.0,0.0};
//   }

// public:
//   Ray ray;
// };

// class VisibilityTester {
// public:
//   VisibilityTester() {}
//   VisibilityTester(const Surfel& p0, const Surfel& p1) : p0(p0), p1(p1) {}
//   bool unoccluded(const Scene& scene) const {
//     Ray ray(p0.p, (p1.p - p0.p).normalized());
//     float t = (p1.p - p0.p).norm();
//     SurfaceInteraction isect;
//     return !scene.intersect_p(ray, &isect) || isect.t > t;
//   }

// public:
//   Surfel p0, p1;
// };

// class Light {
// public:
//   light_flag_e flags;
// public:
//   virtual ~Light() {}
//   Light(int flags) : flags(static_cast<light_flag_e>(flags)) {}
//   virtual ColorXYZ sample_Li(const Surfel& hit, Vector3f* wi, VisibilityTester* vis) = 0;
//   virtual void preprocess(const Scene&) {}
// };

// class PointLight : public Light {
// public:
//   PointLight(const ColorXYZ& color, const Vector3f& position, float intensity)
//       : Light(static_cast<int>(light_flag_e::point) | static_cast<int>(light_flag_e::positional)),
//         color(color), position(position), intensity(intensity) {}

//   virtual ColorXYZ sample_Li(const Surfel& hit, Vector3f* wi, VisibilityTester* vis) override {
//     *wi = (position - hit.p).normalized();
//     *vis = VisibilityTester(hit, Surfel(position));
//     return ((color * intensity / (position - hit.p))^2).norm();
//   }

// private:
//   ColorXYZ color;
//   Vector3f position;
//   float intensity;
// };

// class DirectionalLight : public Light {
// public:
//   DirectionalLight(const ColorXYZ& color, const Vector3f& direction, float intensity)
//       : Light(static_cast<int>(light_flag_e::directional)),
//         color(color), direction(direction.normalized()), intensity(intensity) {}

//   virtual ColorXYZ sample_Li(const Surfel& hit, Vector3f* wi, VisibilityTester* vis) override {
//     *wi = -direction;
//     *vis = VisibilityTester(hit, Surfel(hit.p - direction * 10000.0f));
//     return color * intensity;
//   }

// private:
//   ColorXYZ color;
//   Vector3f direction;
//   float intensity;
// };

// class AmbientLight : public Light {
// public:
//   AmbientLight(const ColorXYZ& color) : Light(static_cast<int>(light_flag_e::ambient)), color(color) {}

//   virtual ColorXYZ sample_Li(const Surfel& hit, Vector3f* wi, VisibilityTester* vis) override {
//     return color;
//   }

// private:
//   ColorXYZ color;
// };

// class SpotLight : public Light {
// public:
//   SpotLight(const ColorXYZ& color, const Vector3f& position, float intensity, float cutoff, float falloff)
//       : Light(static_cast<int>(light_flag_e::spot) | static_cast<int>(light_flag_e::positional)),
//         color(color), position(position), intensity(intensity), cutoff(cutoff), falloff(falloff) {}

//   virtual ColorXYZ sample_Li(const Surfel& hit, Vector3f* wi, VisibilityTester* vis) override {
//     Vector3f dir = position - hit.p;
//     float distance = dir.norm();
//     dir.normalized();
//     float cos_angle = dir.dot(-hit.n);
//     if (cos_angle < std::cos(cutoff * M_PI / 180.0f)) {
//       return ColorXYZ{0.0,0.0,0.0};
//     }
//     if (cos_angle > std::cos((cutoff - falloff) * M_PI / 180.0f)) {
//       *wi = -dir;
//       *vis = VisibilityTester(hit, Surfel(position));
//       return color * intensity / (distance * distance);
//     }
//     float factor = (cos_angle - std::cos((cutoff - falloff) * M_PI / 180.0f)) / (std::cos(cutoff * M_PI / 180.0f) - std::cos((cutoff - falloff) * M_PI / 180.0f));
//     *wi = -dir;
//     *vis = VisibilityTester(hit, Surfel(position));
//     return color * intensity * factor / (distance * distance);
//   }

// private:
//   ColorXYZ color;
//   Vector3f position;
//   float intensity;
//   float cutoff;
//   float falloff;
// };

// }
// #endif // Light _H