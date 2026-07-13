/*
Struct for a cloud.
*/

#pragma once

#include "assets.hpp"

#include "raylib.h"


struct Cloud {
    Cloud(float x, float y, Assets::Texture texture)
        : position({x, y})
        , texture(texture)
    {}

    Vector2         position;
    Assets::Texture texture;
};
