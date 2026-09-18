/*
Class to represent the game background.
This includes the sky as well as the ground.
*/

#pragma once

#include "asset_manager.hpp"

#include "raylib.h"

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
        static constexpr float s_groundMoveSpeed{ 100.0f };

        // Set colours for the sky gradient.
        static constexpr Color s_skyStartColour { 140, 170, 240, 255 };
        static constexpr Color s_skyEndColour   { 76, 94, 232, 255 };

        std::vector<Vector2> m_clouds;
        float                m_groundOffset;
        float                m_secondsToCloudSpawn;
        float                m_secondsToTreeSpawn;
        std::vector<Vector2> m_trees;
};
