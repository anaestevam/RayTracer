#include "math.h"

namespace math{
    RGBColor lerp(const RGBColor &A, const RGBColor &B, float t){
        RGBColor new_color = black;
        new_color.r = (1-t) * A.r + t* B.r;
        new_color.g = (1-t) * A.g + t* B.g;
        new_color.b = (1-t) * A.b + t* B.b;
        return new_color;
    }
}