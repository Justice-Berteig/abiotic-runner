/*
Definition for AssetManager class.
Used to hold all assets, and allow other parts of the program to request access
to those assets.
*/

#pragma once

#include "assets.hpp"

#include "raylib.h"

#include <map>


class AssetManager {
    public:
        AssetManager();
        ~AssetManager();

        /*
        Function allows other parts of the program to request access to a
        texture. If the texture is not already loaded, it is loaded, and a
        reference to the requested texture is returned.
        */
        Texture2D& requestTexture(Assets::Texture requestedTexture);

    private:
        /*
        Map holds all loaded textures.
        */
        std::map<Assets::Texture, Texture2D> m_loadedTextures;

        /*
        Simple functions for loading and unloading textures.
        */
        void m_loadTexture(Assets::Texture targetTexture);
        void m_unloadTexture(Assets::Texture targetTexture);
};
