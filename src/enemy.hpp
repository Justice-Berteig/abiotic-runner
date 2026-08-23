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

        Vector2 position;

    private:
        float m_moveSpeed;
};
