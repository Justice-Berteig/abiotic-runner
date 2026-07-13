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
        static constexpr float s_maxSecondsBetweenClouds{ 8.4 };
        static constexpr float s_minSecondsBetweenClouds{ 1.5 };

        /*
        Get a random number between s_maxSecondsBetweenClouds and
        s_minSecondsBetweenClouds to use as the number of seconds before the
        next cloud will spawn.
        */
        static float s_getSecondsToCloudSpawn();

        std::vector<Cloud> m_clouds;
        float              m_groundMoveSpeed;
        float              m_groundOffset;
        float              m_secondsToCloudSpawn;
};
