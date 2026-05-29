/*
Class to represent the game background.
This includes the sky as well as the ground.
*/

#pragma once

#include "asset_manager.hpp"

#include <memory>


class Background {
    public:
        Background();
        ~Background();

        void tick(double deltaTime);
        void draw(
            float                          renderScale,
            int                            floorStartPosition,
            int                            renderWidth,
            int                            renderHeight,
            std::unique_ptr<AssetManager>& assetManager
        );

    private:
        float m_groundMoveSpeed;
        float m_groundOffset;
};
