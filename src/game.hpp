/*
Class to represent and handle the full game.
*/

#pragma once

#include "asset_manager.hpp"
#include "background.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "type_aliases.hpp"

#include <memory>


class Game {
    public:
        Game();
        ~Game();

        /*
        Run method starts the game and controls the game loop.
        */
        void run();

    private:
        /*
        Store the last frame time so that the time between frames can be
        calculated.
        */
        TimePoint m_lastFrameTime;

        float m_timeToSpawn = 2.0f;

        std::unique_ptr<AssetManager>       m_assetManager;
        std::unique_ptr<Background>         m_background;
        std::vector<std::unique_ptr<Enemy>> m_enemies;
        std::unique_ptr<Player>             m_player;

        /*
        Function calls the tick and draw functions.
        Required for web build.
        */
        void m_tickAndDraw();

        /*
        Tick function for processing every game tick.
        */
        void m_tick();

        /*
        Draw function for drawing every frame.
        */
        void m_draw();

        /*
        Restart function for when the player dies.
        */
        void m_restart();
};
