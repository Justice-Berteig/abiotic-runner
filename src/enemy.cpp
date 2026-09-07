/*
Implementation of Enemy class members.
*/

#include "enemy.hpp"
#include "animation.hpp"
#include "assets.hpp"


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

    // Get dimensions of the enemy's texture to draw its hitbox correctly at
    // ground level.
    Vector2 textureDimensions{
        Assets::getDimensionsForTexture(Assets::Texture::pest)
    };

    Rectangle hitbox{ getCollider() };
    DrawRectangleLines(
        hitbox.x * renderScale,
        (
              floorStartPosition
            - (textureDimensions.y * renderScale)
            + (hitbox.y * renderScale)
        ),
        hitbox.width * renderScale,
        hitbox.height * renderScale,
        RED
    );
}


Rectangle Enemy::getCollider() const {
    // Get dimensions for this enemy's texture to build the collider relative to
    // that.
    Vector2 textureDimensions{
        Assets::getDimensionsForTexture(Assets::Texture::pest)
    };

    return {
        position.x + 3.0f,
        position.y + 16.0f,
        textureDimensions.x - 6,
        textureDimensions.y - 16
    };
}
