/*
Class to represent and handle the full game.
*/

#pragma once

#include "asset_manager.hpp"
#include "background.hpp"
#include "enemy_manager.hpp"
#include "player.hpp"
#include "type_aliases.hpp"


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

        AssetManager m_assetManager;
        Background   m_background;
        EnemyManager m_enemyManager;
        Player       m_player;

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
