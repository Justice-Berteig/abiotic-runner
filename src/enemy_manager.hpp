/*
Used to spawn and keep track of all enemies.
*/

#pragma once

#include "enemy.hpp"

#include <memory>
#include <vector>


class EnemyManager {
    public:
        EnemyManager();
        ~EnemyManager();

        void tick(float deltaTime);
        void draw(
            float                          renderScale,
            int                            floorStartPosition,
            std::unique_ptr<AssetManager>& assetManager
        );

    private:
        static constexpr float s_maxSecondsBetweenEnemies{ 12.0f };
        static constexpr float s_minSecondsBetweenEnemies{  3.0f };
        static constexpr float s_rangeSecondsBetweenEnemies{
            s_maxSecondsBetweenEnemies - s_minSecondsBetweenEnemies
        };

        /*
        Function gets a random number of seconds between
        s_maxSecondsBetweenEnemies and s_minSecondsBetweenEnemies to use as the
        time until the next enemy is spawned.
        */
        static float s_getSecondsToEnemySpawn();

        /*
        Vector to hold all the enemies.
        */
        std::vector<Enemy> m_enemies;
        float              m_secondsToEnemySpawn;
};
