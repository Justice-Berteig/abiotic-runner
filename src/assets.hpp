/*
Define enums to describe all assets.
*/

#pragma once

#include <stdexcept>


namespace Assets {
    enum class Texture {
        dirt
    };

    constexpr const char* getPathForTexture(Texture texture)
    {
        switch(texture)
        {
            case Texture::dirt:
                return "../resources/dirt.png";
            default:
                throw std::runtime_error(
                        "ERROR: Invalid cannot find path for given texture."
                );
        }
    }
};
