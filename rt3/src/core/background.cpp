#include "background.h"

namespace rt3 {
/*!
 * Samples a color base on spherical interpolation of an image ou colored
 * background.
 *
 * @param pixel_ndc Pixel position in NDC space,  in \f$[0:1]\f$.
 * \return The interpolated color.
 */
RGBColor Background::sampleXYZ(const Point2f &pixel_ndc) const {
  //float t_ver = pixel_ndc.x();
  //float t_hor = pixel_ndc.y();
  //RGBColor top = RGBColor::interpolate_color(corners[Corners_e::tl], corners[Corners_e::tr]);
  //RGBColor bottom = RGBColor::interpolate_color(corners[Corners_e::bl], corners[Corners_e::br]);

  //return RGBColor::interpolate_color(t_ver, top, bottom);
  // TODO
  return RGBColor{0, 0, 0};
}

BackgroundColor *create_color_background(const ParamSet &ps) {
  // TODO
  //BackgroundColor::Corners_e corners;
  //corners.bl = retrieve(ps, "bl", white);
  //return new BackgroundColor();
  BackgroundColor* background = nullptr;

  if(ps.count("color")){
    RGBColor c = retrieve( ps, "color", RGBColor());
    background = new BackgroundColor(c, c, c, c);
  }else{
    RGBColor tl = retrieve( ps, "tl", RGBColor());
    RGBColor bl = retrieve( ps, "bl", RGBColor());
    RGBColor tr = retrieve( ps, "tr", RGBColor());
    RGBColor br = retrieve( ps, "br", RGBColor());
    background = new BackgroundColor( bl, tl, tr, br);
  }
  return background;
}
}  // namespace rt3
