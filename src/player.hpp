/*
Player class.
*/

#pragma once

#include "asset_manager.hpp"
#include "enemy.hpp"

#include <cstdint>


class Player {
    public:
        Player();
        ~Player();

        void tick(float deltaTime);
        void draw(
            float         renderScale,
            int           floorStartPosition,
            AssetManager& assetManager
        );

        bool isDead;

        /*
        Method to check for collisions with an enemy.
        */
        void checkCollisionWith(const Enemy& enemy);

    private:
        static constexpr float   m_gravityAcceleration{ 24.6f };
        static constexpr float   m_jumpVelocity       { 22.8f };
        static constexpr float   m_posX               { 32.0f };
        static constexpr uint8_t m_maxHealth          { 5 };

        bool    m_onGround;
        uint8_t m_health;
        float   m_posY;
        float   m_velY;
};
