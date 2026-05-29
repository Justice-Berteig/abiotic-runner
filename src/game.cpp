#include "game.hpp"

#include "assets.hpp"
#include "globals.hpp"
#include "type_aliases.hpp"

#include "raylib.h"

#include <chrono>
#include <iostream>
#include <memory>


Game::Game()
    : m_assetManager(std::make_unique<AssetManager>())
    , m_background(std::make_unique<Background>())
    , m_lastFrameTime(std::chrono::steady_clock::now())
    , m_player(std::make_unique<Player>())
{
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
        targetWindowWidth,
        targetWindowHeight
    );
    SetWindowPosition(
        targetWindowPositionX,
        targetWindowPositionY
    );

    std::cout << "[Game]: created.\n";
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
        double deltaTime{
            std::chrono::duration_cast<TimeMicroseconds>(
                currentFrameTime - m_lastFrameTime
            ).count() / 100000.0
        };
        m_lastFrameTime = currentFrameTime;

        m_tick(deltaTime);

        m_draw();
    }
}


void Game::m_tick(double deltaTime) {
    // Process background tick.
    m_background->tick(deltaTime);

    // Process player tick.
    m_player->tick(deltaTime);
}


void Game::m_draw() {
    BeginDrawing();

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
        if(renderWidth < Globals::minScreenWidth) {
            newScreenWidth = Globals::minScreenWidth;
        }
        if(renderHeight < Globals::minScreenHeight) {
            newScreenHeight = Globals::minScreenHeight;
        }
        SetWindowSize(newScreenWidth, newScreenHeight);
        renderWidth = newScreenWidth;
        renderHeight = newScreenHeight;
    }

    ClearBackground(RAYWHITE);

    // Determine important variables for rendering.
    int tileWidth{ 
        m_assetManager->requestTexture(Assets::Texture::dirt).width
    };
    int renderScale{ (renderWidth / tileWidth) / Globals::minTileColumns };
    int floorStartPosition{
        static_cast<int>(renderHeight * Globals::skyScreenPercentage)
    };

    // Draw Background.
    m_background->draw(
        renderScale,
        floorStartPosition,
        renderWidth,
        renderHeight,
        m_assetManager
    );

    // Draw entities.
    m_player->draw(
        renderScale,
        floorStartPosition,
        m_assetManager
    );

    EndDrawing();
}
