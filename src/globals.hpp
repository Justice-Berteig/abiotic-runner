/*
 * Define some global variables to be used throughout
 * the application.
 */

#pragma once

#include "raylib.h"

namespace Globals {
    inline constexpr unsigned tileSize{ 32 };
    inline constexpr unsigned minScreenWidth{ tileSize * 12 };
    inline constexpr unsigned minScreenHeight{ tileSize * 8 };

    inline constexpr Color skyStartColour { 100, 100, 255, 255 };
    inline constexpr Color skyEndColour   { 100, 100, 120, 255 };

    inline constexpr char dirtTexturePath[] { "../resources/dirt.png" };
}
