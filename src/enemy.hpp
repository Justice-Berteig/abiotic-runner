/*
Class for enemies.
*/

#pragma once

#include "asset_manager.hpp"

#include <raylib.h>

#include <memory>


class Enemy {
    public:
        Enemy();
        ~Enemy();

        void tick(double deltaTime);
        void draw(
            float                          renderScale,
            int                            floorStartPosition,
            std::unique_ptr<AssetManager>& assetManager
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
