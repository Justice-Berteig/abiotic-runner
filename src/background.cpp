/*
Definitions for Background class functions.
*/

#include "background.hpp"

#include "assets.hpp"
#include "cloud.hpp"
#include "globals.hpp"
#include "tree.hpp"

#include "raylib.h"

#include <cmath>


Background::Background()
    : m_clouds()
    , m_groundOffset(0.0f)
    , m_secondsToCloudSpawn(Cloud::s_getSecondsToSpawn())
    , m_secondsToTreeSpawn(Tree::s_getSecondsToSpawn())
    , m_trees()
{
    // Spawn some initial clouds.
    m_clouds.emplace_back(100.0f, 124.0f);
    m_clouds.emplace_back(380.0f, 180.0f);

    // Spawn some initaial trees.
    m_trees.emplace_back(100.0f, 128.0f);
}


Background::~Background() {}


void Background::tick(float deltaTime) {
    // Update ground offset.
    m_groundOffset += s_groundMoveSpeed * deltaTime;
    while(m_groundOffset > 32.0f) m_groundOffset -= 32.0f;

    // Handle cloud spawning.
    if(m_secondsToCloudSpawn > 0.0f) m_secondsToCloudSpawn -= deltaTime;
    else {
        float overflow{ m_secondsToCloudSpawn };
        m_secondsToCloudSpawn = Cloud::s_getSecondsToSpawn() + overflow;
        m_clouds.emplace_back(Cloud::s_getSpawnPosition());
    }

    // Handle tree spawning.
    if(m_secondsToTreeSpawn > 0.0f) m_secondsToTreeSpawn -= deltaTime;
    else {
        float overflow{ m_secondsToTreeSpawn };
        m_secondsToTreeSpawn = Tree::s_getSecondsToSpawn() + overflow;
        m_trees.emplace_back(Tree::s_spawnPosition);
    }
 
    // Update cloud positions.
    for(int i{ 0 }; i < m_clouds.size(); i++) {
        m_clouds[i].x -= Cloud::s_moveSpeed * deltaTime;

        // Remove cloud if off screen.
        if(m_clouds[i].x < -256.0f)
        {
            m_clouds.erase(m_clouds.begin() + i);
            --i;
        }
    }

    // Update tree positions.
    for(int i{ 0 }; i < m_trees.size(); i++) {
        m_trees[i].x -= Tree::s_moveSpeed * deltaTime;

        // Remove cloud if off screen.
        if(m_trees[i].x < -256.0f)
        {
            m_trees.erase(m_trees.begin() + i);
            --i;
        }
    }
}


void Background::draw(
    float         renderScale,
    int           floorStartPosition,
    AssetManager& assetManager
) {
    int renderWidth  { GetRenderWidth() };
    int renderHeight { GetRenderHeight() };

    // Draw sky background.
    DrawRectangleGradientV(
        0,
        0,
        renderWidth,
        renderHeight,
        Globals::skyStartColour,
        Globals::skyEndColour
        );

    // Draw clouds.
    Texture2D cloudTexture{
        assetManager.requestTexture(Cloud::s_texture)
    };

    for(const Vector2& cloud : m_clouds) {
        DrawTextureEx(
            cloudTexture,
            {
                cloud.x * renderScale,
                floorStartPosition - (cloud.y * renderScale),
            },
            0,
            renderScale,
            WHITE
        );
    }

    // Draw trees.
    Texture2D treeTexture{
        assetManager.requestTexture(Tree::s_texture)
    };

    for(const Vector2& tree : m_trees) {
        DrawTextureEx(
            treeTexture,
            {
                tree.x * renderScale,
                floorStartPosition - (tree.y * renderScale),
            },
            0,
            renderScale,
            WHITE
        );
    }

    // Draw dirt floor.
    Texture2D& dirtTexture{
        assetManager.requestTexture(Assets::Texture::dirt)
    };

    int scaledTileSize{ static_cast<int>(dirtTexture.width * renderScale) };

    int tileColumnCount{
        (
            (
                  renderWidth
                + static_cast<int>(std::ceil(m_groundOffset * renderScale))
            ) / scaledTileSize
        ) + 1
    };
    int tileRowCount{
        (
            (
                  renderHeight
                - floorStartPosition
            ) / scaledTileSize
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
