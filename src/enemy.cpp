/*
Implementation of Enemy class members.
*/

#include "enemy.hpp"
#include "animation.hpp"
#include "assets.hpp"
#include "globals.hpp"


Enemy::Enemy(EnemyType type)
    : position(500.0f, 0.0f)
    , m_type  (type)
{
    switch(m_type) {
        case EnemyType::peccary:
            m_animation = Animation(Assets::Texture::peccary_walk);
            m_moveSpeed = 24.0f;
            break;
        case EnemyType::pest:
            m_animation = Animation(Assets::Texture::pest_move);
            m_moveSpeed = 4.0f;
            break;
    }
}


void Enemy::tick(float deltaTime) {
    // Move the enemy forwards.
    // Move speed is combined with player move speed to give impression of
    // moving relative to the player since the player doesn't move relative to
    // the viewport.
    position.x -= (m_moveSpeed + Globals::playerMoveSpeed) * deltaTime;

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

    // Draw enemy collider.
    Rectangle collider{ getCollider() };
    DrawRectangleLines(
        collider.x * renderScale,
        (
              floorStartPosition
            - ((collider.height - position.y) * renderScale)
        ),
        collider.width * renderScale,
        collider.height * renderScale,
        RED
    );
}


Rectangle Enemy::getCollider() const {
    // Get dimensions for this enemy's texture to build the collider relative to
    // that.
    Vector2 textureDimensions{
        Assets::getDimensionsForTexture(m_animation.spriteSheet)
    };

    switch(m_type) {
        case EnemyType::peccary:
            return {
                position.x + 8.0f,
                position.y + 8.0f,
                textureDimensions.x - 28,
                textureDimensions.y -  8
            };
        case EnemyType::pest:
            return {
                position.x + 6.0f,
                position.y + 18.0f,
                textureDimensions.x - 10,
                textureDimensions.y - 18
            };
        default:
            return {
                position.x,
                position.y,
                textureDimensions.x,
                textureDimensions.y
            };
    }
}
