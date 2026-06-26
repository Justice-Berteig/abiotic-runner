/*
Player class.
*/

#pragma once

#include "asset_manager.hpp"

#include <cstdint>
#include <memory>


class Player {
    public:
        Player();
        ~Player();

        void tick(double deltaTime);
        void draw(
            float                          renderScale,
            int                            floorStartPosition,
            std::unique_ptr<AssetManager>& assetManager
        );

    private:
        static constexpr float   m_gravityAcceleration{ 11.6f };
        static constexpr float   m_jumpVelocity       { 16.8f };
        static constexpr uint8_t m_maxHealth          { 5 };

        bool    m_onGround;
        uint8_t m_health;
        float   m_posY;
        float   m_velY;
};
