/*
Class to represent the game background.
This includes the sky as well as the ground.
*/

#pragma once

#include "asset_manager.hpp"
#include "cloud.hpp"

#include <memory>
#include <vector>


class Background {
    public:
        Background();
        ~Background();

        void tick(float deltaTime);
        void draw(
            float                          renderScale,
            int                            floorStartPosition,
            int                            renderWidth,
            int                            renderHeight,
            std::unique_ptr<AssetManager>& assetManager
        );

    private:
        static constexpr float s_maxSecondsBetweenClouds{ 26.4 };
        static constexpr float s_minSecondsBetweenClouds{ 8.5 };

        static constexpr float s_minCloudSpawnX{};
        static constexpr float s_maxCloudSpawnX{};
        static constexpr float s_minCloudSpawnY{};
        static constexpr float s_maxCloudSpawnY{};

        /*
        Get a random number between s_maxSecondsBetweenClouds and
        s_minSecondsBetweenClouds to use as the number of seconds before the
        next cloud will spawn.
        */
        static float s_getSecondsToCloudSpawn();

        /*
        Get a random 
        */
        static Vector2 s_getRandomCloudSpawnPosition();

        std::vector<Cloud> m_clouds;
        float              m_groundMoveSpeed;
        float              m_groundOffset;
        float              m_secondsToCloudSpawn;
};
