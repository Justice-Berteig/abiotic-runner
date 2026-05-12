/*
Define enums to describe all assets.
*/

#pragma once

#include <stdexcept>


namespace Assets {
    enum class Texture {
        dirt,
        player
    };

    constexpr const char* getPathForTexture(Texture texture)
    {
        switch(texture)
        {
            case Texture::dirt:
                return "../resources/dirt.png";
            case Texture::player:
                return "../resources/player.png";
            default:
                throw std::runtime_error(
                        "ERROR: Invalid cannot find path for given texture."
                );
        }
    }
};
