/*
Player class.
*/

#pragma once

#include "animation.hpp"
#include "asset_manager.hpp"
#include "assets.hpp"
#include "enemy.hpp"


class Player {
    public:
        Player();

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

        /*
        Method to get the collision box for the player.
        */
        Rectangle getCollider() const;

        /*
        Functions for getting and incrementing score.
        */
        int  getScore();
        void incrementScore();

    private:
        static constexpr float   m_gravityAcceleration{ 34.6f };
        static constexpr float   m_jumpVelocity       { 22.8f };
        static constexpr float   m_posX               { 32.0f };
        static constexpr Vector2 m_texDimensions      {
            Assets::getDimensionsForTexture(Assets::Texture::player_run)
        };

        bool      m_onGround;
        int       m_score;
        float     m_posY;
        float     m_velY;
        Animation m_anim;
};
