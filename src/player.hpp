/*
Player class.
*/

#pragma once

#include "asset_manager.hpp"
#include "type_aliases.hpp"

#include <memory>


class Player {
public:
    Player();
    ~Player();

    void tick(TimeMicroseconds deltaTime);
    void draw(
        float                          renderScale,
        int                            floorStartPosition,
        std::unique_ptr<AssetManager>& assetManager
    );

private:
    static constexpr uint8_t m_maxHealth{ 5 };
    static constexpr float   m_maxVelY  { 10.0f };

    bool    m_onGround;
    uint8_t m_health;
    float   m_posY;
    float   m_velY;
};
