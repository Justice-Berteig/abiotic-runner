/*
Some constants for cloud decorations.
*/

#pragma once

#include "assets.hpp"
#include "globals.hpp"

#include "raylib.h"

#include <random>


namespace Cloud {
    static constexpr float s_moveSpeed        { 4.0f };
    static constexpr Assets::Texture s_texture{ Assets::Texture::cloud };

    // Create function to get random number of seconds between cloud spawns.
    static constexpr float s_minSecondsBetween { 40.0f };
    static constexpr float s_maxSecondsBetween { 85.0f };
    static std::uniform_real_distribution<float> distSecondsBetween(
        s_minSecondsBetween,
        s_maxSecondsBetween
    );
    static constexpr float s_getSecondsToSpawn() {
        return distSecondsBetween(Globals::gen);
    };

    // Create function to get random spawn position for clouds.
    static constexpr float s_spawnX    { 400.0f };
    static constexpr float s_minSpawnY { 96.0f };
    static constexpr float s_maxSpawnY { 200.0f };
    static std::uniform_real_distribution<float> distSpawnY(
        s_minSpawnY,
        s_maxSpawnY
    );
    static constexpr Vector2 s_getSpawnPosition() {
        return { s_spawnX, distSpawnY(Globals::gen) };
    };
};
