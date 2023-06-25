#ifndef SCREEN_WINDOW_H
#define SCREEN_WINDOW_H

#include "math_base.h"

namespace rt3{

struct ScreenWindow{
    int left, right;
    int bottom, top;

    ScreenWindow() = default;

    ScreenWindow(int l, int r, int b, int t):
    left(l), right(r), bottom(b), top(t){}

    ScreenWindow(const vector<int> &vals):
      ScreenWindow(vals[0], vals[1], vals[2], vals[3]){}

    int width() const { return right - left; }
    int height() const { return top - bottom; }
};

}




#endif