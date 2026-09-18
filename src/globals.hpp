/*
 * Define some global variables to be used throughout
 * the application.
 */

#pragma once

#include <random>

namespace Globals {
    inline constexpr int tileSize       { 32 };
    inline constexpr int minTileColumns { 12 };
    inline constexpr int minTileRows    { 8 };
    inline constexpr int minScreenWidth { tileSize * minTileColumns };
    inline constexpr int minScreenHeight{ tileSize * minTileRows };

    // Determine what percentage of the screen the sky should take up.
    inline constexpr float skyScreenPercentage{ 0.7 };

    // Random number generator used to randomize spawning of decorations and
    // enemies.
    inline static std::random_device rd;
    inline static std::mt19937       gen(rd());
}
