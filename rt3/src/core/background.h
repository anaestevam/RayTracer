#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "math.h"
#include "rt3-base.h"
#include "rt3.h"

namespace rt3
{
  class Background
  {
  public:
    /// Types of color mapping scheme
    enum class mapping_t
    {
      screen = 0, //!< background is assigned to the image screen
      spherical   //!< background is assigne to a sphere surrounding the scene.
    };

  public:
    mapping_t mapping_type; //!< sampling type we use to pick a color.

    /// Ctro receiving a single color for the entire background.
    Background(mapping_t mt = mapping_t::spherical)
        : mapping_type{mt}
    { /* empty */
    }

    virtual ~Background(){/* empty */};
    virtual ColorXYZ sampleXYZ(const Point2f &pixel_ndc);
  };

  class BackgroundColor : public Background
  {
  private:
    /// Each corner has a color associated with.
    /// Corner indices.

  public:
    // Corners_e corners_e;
    /// Ctro receives a list of four colors, for each corner.
    ColorXYZ corners[4] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    enum Corners_e
    {
      bl = 0, //!< Bottom left corner.
      tl = 1, //!< Top left corner.
      tr = 2, //!< Top right corner.
      br = 3  //!< Bottom right corner.
    };

    BackgroundColor(ColorXYZ bl, ColorXYZ tl, ColorXYZ tr, ColorXYZ br)
    {
      corners[Corners_e::bl] = bl;
      corners[Corners_e::tl] = tl;
      corners[Corners_e::tr] = tr;
      corners[Corners_e::br] = br;
    }

    BackgroundColor()
    {
      corners[Corners_e::bl] = {0, 0, 0};
      corners[Corners_e::tl] = {0, 0, 0};
      corners[Corners_e::tr] = {0, 0, 0};
      corners[Corners_e::br] = {0, 0, 0};
    }

    ColorXYZ sampleXYZ(const Point2f &pixel_ndc);
  };

  // factory pattern functions.
  BackgroundColor *create_color_background(const ParamSet &ps, BackgroundColor *background);
} // namespace rt3
#endif
