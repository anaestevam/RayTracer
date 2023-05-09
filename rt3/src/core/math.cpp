#include "rt3.h"

namespace math
{
    ColorXYZ lerp(const ColorXYZ &A, const ColorXYZ &B, float t)
    {
        ColorXYZ new_color = {0, 0, 0};
        new_color[0] = (1 - t) * A[0] + t * B[0];
        new_color[1] = (1 - t) * A[1] + t * B[1];
        new_color[2] = (1 - t) * A[2] + t * B[2];
        return new_color;
    }
}