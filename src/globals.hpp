/*
 * Define some global variables to be used throughout
 * the application.
 */

#pragma once

#include "raylib.h"

namespace Globals {
    inline constexpr int tileSize       { 32 };
    inline constexpr int minTileColumns { 12 };
    inline constexpr int minTileRows    { 8 };
    inline constexpr int minScreenWidth { tileSize * minTileColumns };
    inline constexpr int minScreenHeight{ tileSize * minTileRows };

    inline constexpr float skyScreenPercentage{ 0.7 };

    inline constexpr Color skyStartColour { 100, 100, 255, 255 };
    inline constexpr Color skyEndColour   { 100, 100, 120, 255 };
}
