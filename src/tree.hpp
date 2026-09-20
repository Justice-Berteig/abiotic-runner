/*
Some contants for tree decorations.
*/

#pragma once

#include "assets.hpp"
#include "globals.hpp"

#include "raylib.h"

#include <random>


namespace Tree {
    static constexpr Assets::Texture s_texture { Assets::Texture::tree };

    // Determines how much of the foreground's move speed trees should have.
    // By reducing the speed that trees move compared to the foreground it
    // creates a parallax effect.
    static constexpr float s_parallaxMultiplier { 0.68f };

    // Create function to get random number of seconds between tree spawns.
    static constexpr float s_minSecondsBetween { 4.4f };
    static constexpr float s_maxSecondsBetween { 12.2f };
    static std::uniform_real_distribution<float> distSecondsBetween(
        s_minSecondsBetween,
        s_maxSecondsBetween
    );
    static constexpr float s_getSecondsToSpawn() {
        return distSecondsBetween(Globals::gen);
    };

    // Create function to get random spawn position for trees.
    static constexpr Vector2 s_spawnPosition { 400.0f, 128.0f };
};
