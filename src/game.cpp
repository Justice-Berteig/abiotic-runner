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

    // Initialize window and set some flags.
    InitWindow(
        Globals::minScreenWidth,
        Globals::minScreenHeight,
        "Abiotic Runner"
    );

    SetWindowState(FLAG_VSYNC_HINT);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(Globals::minScreenWidth, Globals::minScreenHeight);

    // Determine inital window size and position based on the current monitor's
    // dimensions.
    int currentMonitorID{ GetCurrentMonitor() };
    int monitorWidth    { GetMonitorWidth(currentMonitorID) };
    int monitorHeight   { GetMonitorHeight(currentMonitorID) };

    unsigned windowScale{ 2 };
    while(
        monitorWidth     > (Globals::minScreenWidth * windowScale)
        && monitorHeight > (Globals::minScreenHeight * windowScale)
    ) {
        ++windowScale;
    }
    if(windowScale > 2) windowScale -= 2;
    else                windowScale -= 1;

    unsigned targetWindowWidth    { Globals::minScreenWidth * windowScale };
    unsigned targetWindowHeight   { Globals::minScreenHeight * windowScale };
    unsigned targetWindowPositionX{ (monitorWidth - targetWindowWidth) / 2 };
    unsigned targetWindowPositionY{ (monitorHeight - targetWindowHeight) / 2 };

    SetWindowSize(
        Globals::minScreenWidth * windowScale,
        Globals::minScreenHeight * windowScale
    );
    SetWindowPosition(
        targetWindowPositionX,
        targetWindowPositionY
    );
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
    // std::cout << deltaTime.count() << '\n';
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

    int tileScale{ (renderWidth / dirtTexture.width) / Globals::minTileColumns };
    int scaledTileSize{ dirtTexture.width * tileScale };
    int floorStartPosition{
        static_cast<int>(renderHeight * Globals::skyScreenPercentage)
    };

    int tileColumnCount{ (renderWidth / scaledTileSize) + 1 };
    int tileRowCount{
        (
            (renderHeight - floorStartPosition)
            / scaledTileSize
        ) + 1
    };

    for(int y{ 0 }; y < tileRowCount; ++y)
    {
        for(int x{ 0 }; x < tileColumnCount; ++x)
        {
            DrawTextureEx(
                dirtTexture,
                {
                    static_cast<float>(x * scaledTileSize),
                    static_cast<float>(floorStartPosition + (y * scaledTileSize))
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
