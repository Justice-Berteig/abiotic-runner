/*
Class to represent the game background.
This includes the sky as well as the ground.
*/

#pragma once

#include "asset_manager.hpp"
#include "cloud.hpp"

#include <vector>


class Background {
    public:
        Background();
        ~Background();

        void tick(float deltaTime);
        void draw(
            float         renderScale,
            int           floorStartPosition,
            int           renderWidth,
            int           renderHeight,
            AssetManager& assetManager
        );

    private:
        static constexpr float s_maxSecondsBetweenClouds{ 85.0f };
        static constexpr float s_minSecondsBetweenClouds{  40.0f };
        static constexpr float s_rangeSecondsBetweenClouds{
            s_maxSecondsBetweenClouds - s_minSecondsBetweenClouds
        };

        static constexpr float s_cloudSpawnX{    400.0f };
        static constexpr float s_maxCloudSpawnY{ 200.0f };
        static constexpr float s_minCloudSpawnY{ 96.0f };
        static constexpr float s_rangeCloudSpawnY{
            s_maxCloudSpawnY - s_minCloudSpawnY
        };

        static constexpr float s_cloudMoveSpeed  = 4.0f;
        static constexpr float s_groundMoveSpeed = 100.0f;

        /*
        Get a random number between s_maxSecondsBetweenClouds and
        s_minSecondsBetweenClouds to use as the number of seconds before the
        next cloud will spawn.
        */
        static float s_getSecondsToCloudSpawn();

        /*
        Get a random Y value to spawn a new cloud at.
        */
        static float s_getRandomCloudSpawnPosition();

        std::vector<Cloud> m_clouds;
        float              m_groundOffset;
        float              m_secondsToCloudSpawn;
};
