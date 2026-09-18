/*
Class to represent the game background.
This includes the sky as well as the ground.
*/

#pragma once

#include "asset_manager.hpp"

#include <vector>


class Background {
    public:
        Background();
        ~Background();

        void tick(float deltaTime);
        void draw(
            float         renderScale,
            int           floorStartPosition,
            AssetManager& assetManager
        );

    private:
        static constexpr float s_groundMoveSpeed = 100.0f;

        std::vector<Vector2> m_clouds;
        float                m_groundOffset;
        float                m_secondsToCloudSpawn;
        float                m_secondsToTreeSpawn;
        std::vector<Vector2> m_trees;
};
