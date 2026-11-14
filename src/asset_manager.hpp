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
        Function allows other parts of the program to request a sound be played.
        If the sound has not already been loaded it will be loaded.
        */
        void playSound(Assets::Sound requestedSound);

        /*
        Function allows other parts of the program to request access to a
        texture. If the texture is not already loaded, it is loaded, and a
        reference to the requested texture is returned.
        */
        const Texture2D& requestTexture(Assets::Texture requestedTexture);

        /*
        Function toggles whether the sounds are muted or not.
        */
        void toggleMute();

    private:
        /*
        Volume for played sounds.
        */
        float m_soundVolume{ 1.0f };

        /*
        Map holds all loaded sounds.
        */
        std::map<Assets::Sound, Sound> m_loadedSounds;

        /*
        Simple functions for loading and unloading sounds.
        */
        void m_loadSound(Assets::Sound targetSound);
        void m_unloadSound(Assets::Sound targetSound);

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
