/*
Definitions for AssetManager class functions.
*/

#include "asset_manager.hpp"
#include "assets.hpp"


AssetManager::AssetManager()
    : m_loadedTextures({})
{}


AssetManager::~AssetManager()
{
    // Unload all loaded textures.
    for(auto it{ m_loadedTextures.begin() }; it != m_loadedTextures.end(); ++it)
        m_unloadTexture(it->first);
}


Texture2D& AssetManager::requestTexture(Assets::Texture requestedTexture)
{
    // Load the requested texture if it has not yet been loaded.
    if(!m_loadedTextures.count(requestedTexture))
        m_loadTexture(requestedTexture);

    return m_loadedTextures[requestedTexture];
}


void AssetManager::m_loadTexture(Assets::Texture targetTexture)
{
    m_loadedTextures[targetTexture] = LoadTexture(
        Assets::getPathForTexture(targetTexture)
    );
}


void AssetManager::m_unloadTexture(Assets::Texture targetTexture)
{
    UnloadTexture(m_loadedTextures[targetTexture]);
    m_loadedTextures.erase(targetTexture);
}
