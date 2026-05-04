#include "game.hpp"

#include "assets.hpp"
#include "globals.hpp"

#include "raylib.h"
#include "type_aliases.hpp"

#include <chrono>
#include <iostream>
#include <memory>


Game::Game()
    : m_lastFrameTime(std::chrono::steady_clock::now())
    , m_assetManager(std::make_unique<AssetManager>())
{
    std::cout << "[Game]: created.\n";

    InitWindow(
        1000,
        1000,
        "Abiotic Runner"
    );
    SetWindowState(FLAG_VSYNC_HINT);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(Globals::minScreenWidth, Globals::minScreenHeight);
}


Game::~Game() {
    CloseWindow();

    std::cout << "[Game]: destroyed.\n";
}


void Game::run() {
    // Main game loop
    while (!WindowShouldClose()) {
        // Calculate delta time
        TimePoint currentFrameTime{ std::chrono::steady_clock::now() };
        TimeMicroseconds deltaTime{
            std::chrono::duration_cast<TimeMicroseconds>(
                currentFrameTime - m_lastFrameTime
            )
        };
        m_lastFrameTime = currentFrameTime;

        m_tick(deltaTime);

        m_draw();
    }
}


void Game::m_tick(TimeMicroseconds deltaTime) {
    std::cout << deltaTime.count() << '\n';
}


void Game::m_draw() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    // Get the dimensions of the window at the beginning of each draw so it
    // updates when the window is resized.
    int renderWidth  { GetRenderWidth() };
    int renderHeight { GetRenderHeight() };

    // Force resize window if too small.
    if(
        renderWidth < Globals::minScreenWidth
        || renderHeight < Globals::minScreenHeight
    ) {
        int newScreenWidth{ renderWidth };
        int newScreenHeight{ renderHeight };
        if(renderWidth < Globals::minScreenWidth) newScreenWidth = Globals::minScreenWidth;
        if(renderHeight < Globals::minScreenHeight) newScreenHeight = Globals::minScreenHeight;
        SetWindowSize(newScreenWidth, newScreenHeight);
        renderWidth = newScreenWidth;
        renderHeight = newScreenHeight;
    }

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
    Texture2D& dirtTexture{ m_assetManager->requestTexture(Assets::Texture::dirt) };

    int minimumTileLength{ 12 };
    int tileScale{ (renderWidth / dirtTexture.width) / minimumTileLength };
    // TODO: Add minimum window size to prevent 0 tileScale
    int scaledTileSize{ dirtTexture.width * tileScale };
    int tileColumnCount{ (renderWidth / scaledTileSize) + 1 };
    int tileRowCount{ (renderHeight / scaledTileSize) + 1 };

    for(int y{ 0 }; y < tileColumnCount; ++y)
    {
        for(int x{ 0 }; x < tileColumnCount; ++x)
        {
            DrawTextureEx(
                dirtTexture,
                {
                    static_cast<float>(x * scaledTileSize),
                    (renderHeight / 2.0f) + (y * scaledTileSize)
                },
                0,
                tileScale,
                WHITE
            );
        }
    }

    // Draw entities.

    EndDrawing();
}
