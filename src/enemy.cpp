/*
Implementation of Enemy class members.
*/

#include "enemy.hpp"
#include "animation.hpp"


Enemy::Enemy()
    : position(500.0f, 0.0f)
    , m_animation(Assets::Texture::pest_move)
    , m_moveSpeed(100.0f)
{}


Enemy::~Enemy() {
}


void Enemy::tick(float deltaTime) {
    // Move the enemy forwards.
    position.x -= m_moveSpeed * deltaTime;

    // Update the animation's current frame.
    updateAnimationCurrentFrame(m_animation, deltaTime);
}


void Enemy::draw(
    float         renderScale,
    int           floorStartPosition,
    AssetManager& assetManager
) {
    int width{ (int)(32 * renderScale) };
    int height{ (int)(32 * renderScale) };

    drawAnimationFrameAt(
        m_animation,
        position.x,
        position.y,
        renderScale,
        floorStartPosition,
        assetManager
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
