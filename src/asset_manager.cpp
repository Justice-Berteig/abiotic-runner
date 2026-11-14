/*
Definitions for AssetManager class functions.
*/

#include "asset_manager.hpp"
#include "assets.hpp"


AssetManager::AssetManager()
    : m_loadedSounds  ({})
    , m_loadedTextures({})
{}


AssetManager::~AssetManager() {
    // Unload all loaded sounds.
    auto soundIterator{ m_loadedSounds.begin() };
    while(soundIterator != m_loadedSounds.end())
    {
        m_unloadSound(soundIterator->first);
        soundIterator = m_loadedSounds.begin();
    }

    // Unload all loaded textures.
    auto textureIterator{ m_loadedTextures.begin() };
    while(textureIterator != m_loadedTextures.end())
    {
        m_unloadTexture(textureIterator->first);
        textureIterator = m_loadedTextures.begin();
    }
}


void AssetManager::playSound(Assets::Sound requestedSound) {
    // Load the requested sound if it has not yet been loaded.
    if(!m_loadedSounds.count(requestedSound))
        m_loadSound(requestedSound);

    // Set the sound volume and play it.
    SetSoundVolume(m_loadedSounds[requestedSound], m_soundVolume);
    PlaySound(m_loadedSounds[requestedSound]);
}


void AssetManager::toggleMute() {
    if(m_soundVolume > 0.0f) m_soundVolume = 0.0f;
    else                     m_soundVolume = 1.0f;
}


const Texture2D& AssetManager::requestTexture(Assets::Texture requestedTexture) {
    // Load the requested texture if it has not yet been loaded.
    if(!m_loadedTextures.count(requestedTexture))
        m_loadTexture(requestedTexture);

    return m_loadedTextures[requestedTexture];
}


void AssetManager::m_loadSound(Assets::Sound targetSound) {
    m_loadedSounds[targetSound] = LoadSound(
        Assets::getPathForSound(targetSound)
    );
}


void AssetManager::m_unloadSound(Assets::Sound targetSound) {
    UnloadSound(m_loadedSounds[targetSound]);
    m_loadedSounds.erase(targetSound);
}


void AssetManager::m_loadTexture(Assets::Texture targetTexture) {
    m_loadedTextures[targetTexture] = LoadTexture(
        Assets::getPathForTexture(targetTexture)
    );
}


void AssetManager::m_unloadTexture(Assets::Texture targetTexture) {
    UnloadTexture(m_loadedTextures[targetTexture]);
    m_loadedTextures.erase(targetTexture);
}
