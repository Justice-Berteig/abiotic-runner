/*
Implementation for EnemyManager class members.
*/

#include "enemy_manager.hpp"


EnemyManager::EnemyManager()
    : m_enemies()
    , m_secondsToEnemySpawn(s_getSecondsToEnemySpawn())
{}


EnemyManager::~EnemyManager() {}


void EnemyManager::tick(
    float   deltaTime,
    Player& player
) {
    // Handle enemy spawning.
    if(m_secondsToEnemySpawn > 0.0f) m_secondsToEnemySpawn -= deltaTime;
    else {
        float overflow{ m_secondsToEnemySpawn };
        m_secondsToEnemySpawn = s_getSecondsToEnemySpawn() + overflow;
        m_enemies.emplace_back();
    }

    // Do tick for each enemy + check for collision with player.
    for(int i{ 0 }; i < m_enemies.size(); i++) {
        m_enemies[i].tick(deltaTime);

        if(!player.isDead) player.checkCollisionWith(m_enemies[i]);

        // Remove enemy if off screen.
        if(m_enemies[i].position.x < -128.0f)
        {
            m_enemies.erase(m_enemies.begin() + i);
            --i;
        }
    }
}


void EnemyManager::draw(
    float         renderScale,
    int           floorStartPosition,
    AssetManager& assetManager
) {
    // Draw each enemy.
    for(Enemy& enemy : m_enemies) {
        enemy.draw(renderScale, floorStartPosition, assetManager);
    }
}


float EnemyManager::s_getSecondsToEnemySpawn() {
    return (((float)rand() / RAND_MAX) * s_rangeSecondsBetweenEnemies)
            + s_minSecondsBetweenEnemies;
}
