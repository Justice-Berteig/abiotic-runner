/*
Implementation for EnemyManager class members.
*/

#include "enemy_manager.hpp"


EnemyManager::EnemyManager()
{
    m_secondsToEnemySpawn = s_getSecondsToEnemySpawn();
}


EnemyManager::~EnemyManager()
{
}


void EnemyManager::tick(float deltaTime)
{
    // Handle enemy spawning.
    if(m_secondsToEnemySpawn > 0.0f) m_secondsToEnemySpawn -= deltaTime;
    else {
        float overflow{ m_secondsToEnemySpawn };
        m_secondsToEnemySpawn = s_getSecondsToEnemySpawn() + overflow;
        //m_clouds.emplace_back(s_cloudSpawnX, s_getRandomCloudSpawnPosition());
    }
}


void EnemyManager::draw(
    float                          renderScale,
    int                            floorStartPosition,
    std::unique_ptr<AssetManager>& assetManager
)
{
}


float EnemyManager::s_getSecondsToEnemySpawn()
{
    return (((float)rand() / RAND_MAX) * s_rangeSecondsBetweenEnemies)
            + s_minSecondsBetweenEnemies;
}
