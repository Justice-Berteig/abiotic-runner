/*
Implementation of Enemy class members.
*/

#include "enemy.hpp"


Enemy::Enemy()
    : position(500.0f, 0.0f)
    , m_moveSpeed(100.0f)
{}


Enemy::~Enemy() {
}


void Enemy::tick(float deltaTime) {
    position.x -= m_moveSpeed * deltaTime;
}


void Enemy::draw(
    float         renderScale,
    int           floorStartPosition,
    AssetManager& assetManager
) {
    int width{ (int)(32 * renderScale) };
    int height{ (int)(32 * renderScale) };

    DrawRectangle(
        (int)(position.x * renderScale),
        (int)(floorStartPosition + position.y - height),
        width,
        height,
        RED
    );
}


Rectangle Enemy::getCollider() const {
    return {
        position.x - 16.0f,
        position.y -16.0f,
        32.0f,
        32.0f
    };
}
