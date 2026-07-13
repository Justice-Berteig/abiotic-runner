/*
Implementations for Player class.
*/

#include "player.hpp"

#include "raylib.h"


Player::Player()
    : m_onGround(true)
    , m_health(m_maxHealth)
    , m_posY(0)
{}


Player::~Player() {}


void Player::tick(float deltaTime) {
    if(m_onGround && IsKeyPressed(KEY_SPACE)) {
        // If on ground and spacebar pressed, apply jump.
        m_onGround = false;
        m_velY     = m_jumpVelocity;
    }else if(!m_onGround) {
        // Aplly gravity if not on ground.
        m_velY -= m_gravityAcceleration * deltaTime;
    }

    m_posY += m_velY * 10 * deltaTime;

    if(m_posY <= 0) {
        m_posY = 0;
        m_velY = 0;
        m_onGround = true;
    }
}


void Player::draw(
    float                          renderScale,
    int                            floorStartPosition,
    std::unique_ptr<AssetManager>& assetManager
) {
    Texture2D playerSprite{
        assetManager->requestTexture(Assets::Texture::player)
    };
    DrawTexturePro(
        playerSprite,
        {0, 0, (float)playerSprite.width, (float)playerSprite.height},
        {
            m_posX * renderScale,
            (floorStartPosition - (m_posY * renderScale)) - (32 * renderScale),
            playerSprite.width * renderScale,
            playerSprite.height * renderScale
        },
        {0, 0},
        0.0f,
        WHITE
    );
}


bool Player::isCollidingWith(const std::unique_ptr<Enemy>& enemy) {
    Rectangle enemyCollider{ enemy->getCollider() };
    Rectangle playerCollider{
        m_posX - 16.0f,
        m_posY - 16.0f,
        32.0f,
        32.0f
    };

    if(
        enemyCollider.x <= playerCollider.x + playerCollider.width
        && playerCollider.x <= enemyCollider.x + enemyCollider.width
        && enemyCollider.y <= playerCollider.y + playerCollider.height
        && playerCollider.y <= enemyCollider.y + enemyCollider.height
    )
        return true;
    else
        return false;
}
