/*
Class for enemies.
*/

#pragma once

#include "asset_manager.hpp"

#include <raylib.h>


class Enemy {
    public:
        Enemy();
        ~Enemy();

        void tick(float deltaTime);
        void draw(
            float         renderScale,
            int           floorStartPosition,
            AssetManager& assetManager
        );

        /*
        Public function for getting the collider of this enemy.
        */
        Rectangle getCollider() const;

        bool isDead;

    private:
        float m_distanceAboveGround;
        float m_moveSpeed;
        float m_xPos;
};
