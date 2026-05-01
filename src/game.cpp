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

    // Draw dirt floor.
    Texture2D& tex{ m_assetManager->requestTexture(Assets::Texture::dirt) };

    int desiredTileLength{ 12 };
    int tileScale{ (renderWidth / tex.width) / desiredTileLength };
    std::cout << tileScale << '\n';

    for(int i{ 0 }; i < desiredTileLength; ++i)
    {
        DrawTextureEx(
            tex,
            {
                static_cast<float>(i * tex.width * tileScale),
                renderHeight / 2.0f
            },
            0,
            tileScale,
            WHITE
        );
    }

    int remainingSpace{ renderWidth - (desiredTileLength * tex.width * tileScale) };
    std::cout << remainingSpace / (tex.width * tileScale) << '\n';

    EndDrawing();
}
