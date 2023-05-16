#include "background.h"

namespace rt3
{

  ColorXYZ Background::sampleXYZ(const Point2f &pixel_ndc)
  {
    return ColorXYZ{0, 0, 0};
  }

  ColorXYZ Background::sampleXYZ(const Vector3f &pixel_ndc)
  {
    return ColorXYZ{0, 0, 0};
  }

  /*!
   * Samples a color base on spherical interpolation of an image ou colored
   * background.
   *
   * @param pixel_ndc Pixel position in NDC space,  in \f$[0:1]\f$.
   * \return The interpolated color.
   */
  ColorXYZ BackgroundColor::sampleXYZ(const Point2f &pixel_ndc)
  {
    float t_ver = pixel_ndc[0];
    float t_hor = pixel_ndc[1];

    //std::cout << t_ver << " " << t_hor << ",";

    ColorXYZ top = math::lerp(corners[Corners_e::tl], corners[Corners_e::tr], t_hor);
    ColorXYZ bottom = math::lerp(corners[Corners_e::bl], corners[Corners_e::br], t_hor);

    return math::lerp(top, bottom, t_ver);
  }

    ColorXYZ BackgroundColor::sampleXYZ(const Vector3f &pixel_ndc)
  {
    float t_ver = pixel_ndc[0];
    float t_hor = pixel_ndc[1];

    //std::cout << t_ver << " " << t_hor << ",";

    ColorXYZ top = math::lerp(corners[Corners_e::tl], corners[Corners_e::tr], t_hor);
    ColorXYZ bottom = math::lerp(corners[Corners_e::bl], corners[Corners_e::br], t_hor);

    return math::lerp(top, bottom, t_ver);
  }

  BackgroundColor *create_color_background(const ParamSet &ps, BackgroundColor *background)
  {
    if (ps.count("color"))
    {
      ColorXYZ c = retrieve(ps, "color", ColorXYZ());
      BackgroundColor *nc = new BackgroundColor(c, c, c, c);
      if (background != nullptr)
      {
        delete background;
      }
      background = nc;
    }
    else
    {
      ColorXYZ tl = retrieve(ps, "tl", ColorXYZ());
      ColorXYZ bl = retrieve(ps, "bl", ColorXYZ());
      ColorXYZ tr = retrieve(ps, "tr", ColorXYZ());
      ColorXYZ br = retrieve(ps, "br", ColorXYZ());
      BackgroundColor *nc = new BackgroundColor(bl, tl, tr, br);
      if (background != nullptr)
      {
        delete background;
      }
      background = nc;
    }
    return background;
  }
} // namespace rt3
