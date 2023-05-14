#include "film.h"
#include <cstring>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <functional>
#include "api.h"
#include "image_io.h"
#include "paramset.h"

namespace rt3
{

  Film::Film(const Point2i &resolution, const std::string &filename, image_type_e imgt)
      : m_full_resolution{resolution}, m_filename{filename}, m_image_type{imgt}
  {
    m_pixels.resize(m_full_resolution[0] * m_full_resolution[1]);
  }

  Film::~Film()
  {
  }

  void Film::add_sample(const Point2f &pixel_coord, const ColorXYZ &pixel_color){

    float x = (pixel_coord[0] * m_full_resolution[0]);
    float y = (pixel_coord[1] * m_full_resolution[1]);
    if (x < m_full_resolution[0] && y < m_full_resolution[1]){
      size_t index = y * m_full_resolution[0] + x;
           for (int i = 0; i < 3; i++)
           {
               m_pixels[index][i] += pixel_color[i];
           }
    }
  }

  void Film::write_image(size_t w, size_t h, size_t d, const std::string &file_name)
  {
    unsigned char *data = new unsigned char[w * h * 3];

    for (size_t y = 0; y < h; y++){
      for (size_t x = 0; x < w; x++){
        size_t index = y * w + x;
        float r = m_pixels[index][0] / d;
        float g = m_pixels[index][1] / d;
        float b = m_pixels[index][2] / d;
        data[index * 3 + 0] = static_cast<unsigned char>(r);
        data[index * 3 + 1] = static_cast<unsigned char>(g);
        data[index * 3 + 2] = static_cast<unsigned char>(b);
      }
    }

    switch (m_image_type) {
           case image_type_e::PPM3:
               save_ppm3(data, w, h, 3, file_name.c_str());
               break;
           case image_type_e::PPM6:
               save_ppm6(data, w, h, 3, file_name.c_str());
               break;
           case image_type_e::PNG:
               save_png(data, w, h, 3, file_name.c_str());
               break;
       }

    delete[] data;
  }

  // Factory function pattern.
  // This is the function that retrieves from the ParamSet object
  // all the information we need to create a Film object.
  Film *create_film(const ParamSet &ps)
  {
    std::cout << ">>> Inside create_film()\n";
    std::string filename;
    // Let us check whether user has provided an output file name via
    // command line arguments in main().
    if (API::curr_run_opt.outfile != "")
    {
      // Retrieve filename defined via CLI.
      filename = API::curr_run_opt.outfile;
      // Retrieve another filename, now from the ParamSet object.
      std::string filename_from_file = retrieve(ps, "filename", std::string{""});
      if (filename_from_file != "") // We also get a filename from scene file...
        RT3_WARNING(string{"Output filename supplied on command line, \""} + API::curr_run_opt.outfile + string{"\" is overriding filename provided in scene "
                                                                                                                "description file, \""} +
                    filename_from_file);
    }
    else
    {
      // Try yo retrieve filename from scene file.
      filename = retrieve(ps, "filename", std::string{"image.png"});
    }

    // Read resolution.
    // Aux function that retrieves info from the ParamSet.
    int xres = retrieve(ps, "x_res", int(1280));
    // Aux function that retrieves info from the ParamSet.
    int yres = retrieve(ps, "y_res", int(720));
    // Quick render?
    if (API::curr_run_opt.quick_render == true)
    {
      // decrease resolution.
      xres = std::max(1, xres / 4);
      yres = std::max(1, yres / 4);
    }

    // TODO
    // Read crop window information.
    std::vector<real_type> cw = retrieve(ps, "crop_window", std::vector<real_type>{0, 1, 0, 1});
    std::cout << "Crop window ";
    for (const auto &e : cw)
      std::cout << e << " ";
    std::cout << '\n';

    // Note that the image type is fixed here. Must be read from ParamSet, though.
    return new Film(Point2i{xres, yres}, filename, Film::image_type_e::PNG);
  }
} // namespace rt3
