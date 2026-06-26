/*
Implementation of Enemy class members.
*/

#include "enemy.hpp"


Enemy::Enemy()
    : isDead(false)
    , m_distanceAboveGround(0.0f)
    , m_moveSpeed(100.0f)
    , m_xPos(500.0f)
{
}


Enemy::~Enemy() {
}


void Enemy::tick(double deltaTime) {
    m_xPos -= m_moveSpeed * deltaTime;
}


void Enemy::draw(
    float                          renderScale,
    int                            floorStartPosition,
    std::unique_ptr<AssetManager>& assetManager
) {
    int width{ (int)(32 * renderScale) };
    int height{ (int)(32 * renderScale) };

    DrawRectangle((int)(m_xPos * renderScale), floorStartPosition - height, width, height, RED);
}


Rectangle Enemy::getCollider() const {
    return {
        m_xPos - 16.0f,
        -16.0f,
        32.0f,
        32.0f
    };
}
