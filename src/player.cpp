/*
Implementations for Player class.
*/

#include "player.hpp"

#include "type_aliases.hpp"

#include "raylib.h"


Player::Player()
    : m_onGround(true)
    , m_health(m_maxHealth)
    , m_posY(0)
{}


Player::~Player() {}


void Player::tick(TimeMicroseconds deltaTime) {
    if(m_onGround && IsKeyPressed(KEY_SPACE)) {
        m_onGround = false;
        m_velY     = m_maxVelY;
    }else if(!m_onGround) {
        m_velY -= 0.0001f * deltaTime.count();
    }

    m_posY += m_velY * (0.0001f * deltaTime.count());

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
            32 * renderScale,
            (floorStartPosition - (m_posY * renderScale)) - (32 * renderScale),
            playerSprite.width * renderScale,
            playerSprite.height * renderScale
        },
        {0, 0},
        0.0f,
        WHITE
    );
}
