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
    drawAnimationFrameAt(
        m_animation,
        position.x,
        position.y,
        renderScale,
        floorStartPosition,
        assetManager
    );

    Rectangle hitbox{ getCollider() };
    DrawRectangleLines(
        hitbox.x * renderScale,
        floorStartPosition - (32 * renderScale) + (hitbox.y * renderScale),
        hitbox.width * renderScale,
        hitbox.height * renderScale,
        RED
    );
}


Rectangle Enemy::getCollider() const {
    return {
        position.x + 2.0f,
        position.y + 14.0f,
        28.0f,
        18.0f
    };
}
