/*
Definitions for Background class functions.
*/

#include "background.hpp"

#include "globals.hpp"

#include "raylib.h"

#include <cmath>


Background::Background()
    : m_clouds()
    , m_groundMoveSpeed(100.0f)
    , m_groundOffset(0.0f)
    , m_secondsToCloudSpawn(s_getSecondsToCloudSpawn())
{
    m_clouds.emplace_back(100.0f, 40.0f, Assets::Texture::dirt);
    m_clouds.emplace_back(380.0f, 180.0f, Assets::Texture::dirt);
}


Background::~Background() {}


void Background::tick(float deltaTime) {
    // Handle cloud spawning.
    if(m_secondsToCloudSpawn > 0.0) m_secondsToCloudSpawn -= deltaTime;
    else {
        float overflow{ m_secondsToCloudSpawn };
        m_secondsToCloudSpawn = s_getSecondsToCloudSpawn() + overflow;
        m_clouds.emplace_back(1.0f, 1.0f, Assets::Texture::dirt);
    }
 
    // Update ground offset.
    m_groundOffset += m_groundMoveSpeed * deltaTime;
    while(m_groundOffset > 32.0f) m_groundOffset -= 32.0f;

    // Update cloud positions.
    for(Cloud& cloud : m_clouds) {
        cloud.position.x -= deltaTime;
    }
}


void Background::draw(
    float                          renderScale,
    int                            floorStartPosition,
    int                            renderWidth,
    int                            renderHeight,
    std::unique_ptr<AssetManager>& assetManager
) {
    // Draw sky background.
    DrawRectangleGradientV(
        0,
        0,
        renderWidth,
        renderHeight,
        Globals::skyStartColour,
        Globals::skyEndColour
        );

    // Draw dirt floor.
    Texture2D& dirtTexture{
        assetManager->requestTexture(Assets::Texture::dirt)
    };

    int scaledTileSize{ static_cast<int>(dirtTexture.width * renderScale) };

    int tileColumnCount{
        (
            (renderWidth + (int)std::ceil(m_groundOffset))
            / scaledTileSize
        ) + 1
    };
    int tileRowCount{
        (
            (renderHeight - floorStartPosition)
            / scaledTileSize
        ) + 1
    };

    for(int y{ 0 }; y < tileRowCount; ++y) {
        for(int x{ 0 }; x < tileColumnCount; ++x) {
            DrawTextureEx(
                dirtTexture,
                {
                    static_cast<float>(
                        (x * scaledTileSize) - (m_groundOffset * renderScale)
                    ),
                    static_cast<float>(
                        floorStartPosition + (y * scaledTileSize)
                    )
                },
                0,
                renderScale,
                WHITE
            );
        }
    }

    // Draw clouds.
    for(const Cloud& cloud : m_clouds) {
        DrawRectangle(
            cloud.position.x * renderScale,
            floorStartPosition - (cloud.position.y * renderScale),
            10 * renderScale,
            10 * renderScale,
            WHITE
        );
    }
}


float Background::s_getSecondsToCloudSpawn() {
    return 3.0;
}
