#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "math.h"
#include "rt3-base.h"
#include "rt3.h"

namespace rt3 {
// TODO: Create a virtual class Background and derive BackgroundColor,
// BackgroundSphereImage, BackgroundSkyBoxImage, posterior se tiver tempo.
/*!
 * A background is basically a rectangle, have a color associated to each
 * corner. A background might be sampled based on a normalized coordinate in
 * \f$[0,1]^2.\f$. We generate samples with bilinear interpolation of the corner
 * colors. We consider the corners in a circular clockwise order, starting at
 * the lower-left corner.
 *
 * Alternatively, a background might be a regular image.
 */
class Background {
 public:
  /// Types of color mapping scheme
  enum class mapping_t {
    screen = 0,  //!< background is assigned to the image screen
    spherical    //!< background is assigne to a sphere surrounding the scene.
  };

 public:
  mapping_t mapping_type;  //!< sampling type we use to pick a color.

  /// Ctro receiving a single color for the entire background.
  Background(mapping_t mt = mapping_t::spherical)
      : mapping_type{mt} { /* empty */
  }

  virtual ~Background(){/* empty */};
  Spectrum sampleXYZ(const Point2f &pixel_ndc) const;
};

class BackgroundColor : public Background {

 public:
  /// Each corner has a color associated with.
  // Spectrum corners[4] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  /// Corner indices.
  enum Corners_e {
    bl = 0,  //!< Bottom left corner.
    tl = 1,      //!< Top left corner.
    tr = 2,      //!< Top right corner.
    br = 3     //!< Bottom right corner.
  };



  Corners_e corners_e;
  /// Ctro receives a list of four colors, for each corner.
  BackgroundColor(const Corners_e &corners) {
    corners_e = corners;
  }

  virtual ~BackgroundColor(){};
};

// factory pattern functions.
BackgroundColor *create_color_background(const ParamSet &ps);
}  // namespace rt3
#endif
