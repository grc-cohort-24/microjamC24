#pragma once
#include <bn_display.h>

namespace mck {
    inline constexpr int MAX_X = bn::display::width() / 2;
    inline constexpr int MIN_X = -MAX_X;
    inline constexpr int MAX_Y = bn::display::height() / 2;
    inline constexpr int MIN_Y = -MAX_Y;
}