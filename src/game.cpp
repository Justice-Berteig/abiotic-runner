#include "game.hpp"

#include "assets.hpp"
#include "globals.hpp"
#include "type_aliases.hpp"

#include "raylib.h"

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>


Game::Game()
    : m_assetManager()
    , m_background()
    , m_enemyManager()
    , m_lastFrameTime(std::chrono::steady_clock::now())
    , m_player()
{
    // Set seed for random number generator
    std::srand(std::time({}));

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
           monitorWidth  > (Globals::minScreenWidth * windowScale)
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
    while (!WindowShouldClose()) {
        m_tick();
        m_draw();
    }
}


void Game::m_tick() {
    // Calculate delta time
    TimePoint currentFrameTime{ std::chrono::steady_clock::now() };
    float deltaTime{
        std::chrono::duration_cast<TimeMicroseconds>(
            currentFrameTime - m_lastFrameTime
        ).count() / 1000000.0f
    };
    m_lastFrameTime = currentFrameTime;

    // Process background tick.
    m_background.tick(deltaTime);

    // Process player tick.
    m_player.tick(deltaTime);

    // Process enemy ticks
    m_enemyManager.tick(
        deltaTime,
        m_player
    );

    // Restart if player died.
    if(m_player.isDead) m_restart();
}


void Game::m_draw() {
    BeginDrawing();

    // Get the dimensions of the window at the beginning of each draw so it
    // updates when the window is resized.
    int renderWidth  { GetRenderWidth() };
    int renderHeight { GetRenderHeight() };

    // Force resize window if too small.
    if(
           renderWidth  < Globals::minScreenWidth
        || renderHeight < Globals::minScreenHeight
    ) {
        int newScreenWidth { renderWidth };
        int newScreenHeight{ renderHeight };

        if(renderWidth < Globals::minScreenWidth) {
            newScreenWidth = Globals::minScreenWidth;
        }
        if(renderHeight < Globals::minScreenHeight) {
            newScreenHeight = Globals::minScreenHeight;
        }

        SetWindowSize(newScreenWidth, newScreenHeight);
    }

    ClearBackground(RAYWHITE);

    // Determine important variables for rendering.
    int tileWidth{ static_cast<int>(
        Assets::getDimensionsForTexture(Assets::Texture::dirt).x
    )};
    int renderScale{ (renderWidth / tileWidth) / Globals::minTileColumns };
    int floorStartPosition{
        static_cast<int>(renderHeight * Globals::skyScreenPercentage)
    };

    // Draw Background.
    m_background.draw(
        renderScale,
        floorStartPosition,
        m_assetManager
    );

    // Draw player.
    m_player.draw(
        renderScale,
        floorStartPosition,
        m_assetManager
    );

    // Draw enemies.
    m_enemyManager.draw(
        renderScale,
        floorStartPosition,
        m_assetManager
    );

    EndDrawing();
}


void Game::m_restart() {
    m_background    = Background();
    m_enemyManager  = EnemyManager();
    m_lastFrameTime = std::chrono::steady_clock::now();
    m_player        = Player();

    std::cout << "[Game]: restarted.\n";
}
