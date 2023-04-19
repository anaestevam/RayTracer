#ifndef MATH_H
#define MATH_H 1

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
#include "commom.h"
#include "rt3.h"
// #include <unordered_map>
// using std::string;
// #include <algorithm>
// #include <tuple>
// #include <utility>
// using std::tuple;
// #include <array>
namespace math{

inline float Lerp(float t, float v1, float v2) {
  return (1.f - t) * v1 + t * v2;
}

}
#endif  // MATH_H
