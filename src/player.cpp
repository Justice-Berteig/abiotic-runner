/*
Implementations for Player class.
*/

#include "player.hpp"

#include "animation.hpp"
#include "assets.hpp"
#include "raylib.h"


Player::Player()
    : isDead(false)
    , m_onGround(true)
    , m_health(m_maxHealth)
    , m_posY(0)
    , m_velY(0)
    , m_anim(Assets::Texture::player_run)
{}


Player::~Player() {}


void Player::tick(float deltaTime) {
    if(m_onGround && IsKeyPressed(KEY_SPACE)) {
        // If on ground and spacebar pressed, apply jump.
        m_onGround = false;
        m_velY     = -m_jumpVelocity;
    }else if(!m_onGround) {
        // Apply gravity if not on ground.
        m_velY += m_gravityAcceleration * deltaTime;
    }

    m_posY += m_velY * 10 * deltaTime;

    if(m_posY >= 0) {
        m_posY = 0;
        m_velY = 0;
        m_onGround = true;
    }

    // Update animation's current frame.
    updateAnimationCurrentFrame(m_anim, deltaTime);
}


void Player::draw(
    float         renderScale,
    int           floorStartPosition,
    AssetManager& assetManager
) {
    // Update animation based on player state.
    if(
           m_onGround
        && m_anim.spriteSheet != Assets::Texture::player_run
    ) {
        m_anim = Animation(Assets::Texture::player_run);
    }
    else if(
           !m_onGround
        && m_velY < -3.0f
        && m_anim.spriteSheet != Assets::Texture::player_jump
    ) {
        m_anim = Animation(Assets::Texture::player_jump);
    }
    else if(
           !m_onGround
        && m_velY >= -3.0f
        && m_anim.spriteSheet != Assets::Texture::player_fall
    ) {
        m_anim = Animation(Assets::Texture::player_fall);
    }

    // Draw animation.
    drawAnimationFrameAt(
        m_anim,
        m_posX,
        m_posY,
        renderScale,
        floorStartPosition,
        assetManager
    );

    Rectangle hitbox{ getCollider() };
    DrawRectangleLines(
        hitbox.x * renderScale,
        (
              floorStartPosition
            - (m_texDimensions.y * renderScale)
            + (hitbox.y * renderScale)
        ),
        hitbox.width * renderScale,
        hitbox.height * renderScale,
        RED
    );
}


void Player::checkCollisionWith(const Enemy& enemy) {
    Rectangle enemyCollider{  enemy.getCollider() };
    Rectangle playerCollider{ getCollider() };

    if(
           enemyCollider.x  <= playerCollider.x + playerCollider.width
        && playerCollider.x <= enemyCollider.x  + enemyCollider.width
        && enemyCollider.y  <= playerCollider.y + playerCollider.height
        && playerCollider.y <= enemyCollider.y  + enemyCollider.height
    )
        isDead = true;
}


Rectangle Player::getCollider() const {
    return {
        m_posX + 16.0f,
        m_posY + 6.0f,
        m_texDimensions.x - 32,
        m_texDimensions.y - 6
    };
}
