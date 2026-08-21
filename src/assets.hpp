/*
Define enums to describe all assets.
*/

#pragma once

#include <stdexcept>

#include "raylib.h"


namespace Assets {
    enum class Texture {
        cloud,
        dirt,
        pest,
        player
    };


    constexpr const char* getPathForTexture(Texture texture) {
        switch(texture) {
            case Texture::cloud:
                return "../resources/cloud.png";
            case Texture::dirt:
                return "../resources/dirt.png";
            case Texture::pest:
                return "../resources/pest.png";
            case Texture::player:
                return "../resources/player.png";
            default:
                throw std::runtime_error(
                    "ERROR: Invalid cannot find path for given texture."
                );
        }
    }


    constexpr const Vector2 getDimensionsForTexture(Texture texture) {
        switch(texture) {
            case Texture::cloud:
                return {  10,  10 };
            case Texture::dirt:
                return {  32,  32 };
            case Texture::pest:
                return {  32,  32 };
            case Texture::player:
                return { 128,  64 };
            default:
                throw std::runtime_error(
                    "ERROR: No dimensions set for given texture."
                );
        }
    }
};
