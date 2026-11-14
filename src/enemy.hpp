/*
Class for enemies.
*/

#pragma once

#include "animation.hpp"
#include "asset_manager.hpp"

#include <raylib.h>


enum class EnemyType {
    instructions,
    peccary,
    pest
};


class Enemy {
    public:
        Enemy(EnemyType type);

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
        float     m_moveSpeed;
        Animation m_animation;
        EnemyType m_type;
};
