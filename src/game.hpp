#pragma once

#include "asset_manager.hpp"
#include "background.hpp"
#include "player.hpp"
#include "type_aliases.hpp"

#include <memory>


class Game {
    public:
        Game();
        ~Game();

        /*
         * Run method starts the game and controls the game loop.
         */
        void run();

    private:
        /*
        Store the last frame time so that the time between frames can be
        calculated.
        */
        TimePoint m_lastFrameTime;

        std::unique_ptr<AssetManager> m_assetManager;
        std::unique_ptr<Background>   m_background;
        std::unique_ptr<Player>       m_player;

        /*
         * Tick function for processing every game tick.
         * Takes an argument `deltaTime` that represents the time in seconds
         * since the last tick.
         */
        void m_tick(double deltaTime);

        /*
         * Draw function for drawing every frame.
         */
        void m_draw();
        void m_drawBackground(
            float renderScale,
            int   floorStartPosition,
            int   renderWidth,
            int   renderHeight
        );
};
