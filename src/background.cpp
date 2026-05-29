/*
Definitions for Background class functions.
*/

#include "background.hpp"

#include "globals.hpp"

#include "raylib.h"

#include <cmath>


Background::Background()
    : m_groundMoveSpeed(10.0f)
    , m_groundOffset(0.0f)
{}


Background::~Background() {}


void Background::tick(double deltaTime) {
    // Update ground offset.
    m_groundOffset += m_groundMoveSpeed * deltaTime;
    while(m_groundOffset > 32.0f) m_groundOffset -= 32.0f;
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
}
