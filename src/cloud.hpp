/*
Struct for a cloud.
*/

#pragma once

#include "assets.hpp"

#include "raylib.h"


struct Cloud {
    Cloud(float x, float y);

    Vector2 position;

    static constexpr Assets::Texture texture{ Assets::Texture::cloud };
};
