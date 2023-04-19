#ifndef COMMOM_H
#define COMMOM_H 1

// #include <cassert>
// #include <cmath>
// #include <cstdlib>
// #include <cstdint>
// #include <iostream>
// #include <memory>
// #include <vector>
// using std::vector;
// #include <map>
// #include <stack>
// #include <string>
#include "rt3.h"
#include "math.h"
// #include <unordered_map>
// using std::string;
// #include <algorithm>
// #include <tuple>
// #include <utility>
// using std::tuple;
// #include <array>
using std::array;

struct RGBColor {
  float r;
  float g;
  float b;
};

constexpr RGBColor red{255, 0, 0};
constexpr RGBColor green{0, 255, 0};
constexpr RGBColor blue{0, 0, 255};
constexpr RGBColor black{0, 0, 0};
constexpr RGBColor white{255, 255, 255};

static inline RGBColor interpolate_color(const float t, const RGBColor &a, const RGBColor &b){
  return RGBColor{{
    //Lerp(t, a.x(), b.x()),
    //Lerp(t, a.y(), b.y()),
    //Lerp(t, a.z(), b.z()),
  }};
}

#endif  // COMMOM_H
