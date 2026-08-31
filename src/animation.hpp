/*
 * Structure for an animation.
 */

#pragma once

#include "asset_manager.hpp"
#include "assets.hpp"


struct Animation {
    Animation(Assets::Texture spriteSheet);

    Assets::Texture spriteSheet;
    int             currentFrame;
    int             totalFrames;
    float           lastFrameTime;

    static constexpr int   s_framesPerSeconds { 12 };
    static constexpr float s_timeBetweenFrames{ 1.0f / s_framesPerSeconds };
};


/*
 * Function to draw the current frame of a given animation.
 */
void drawAnimationFrameAt(
    const Animation& anim,
    float            x,
    float            y,
    float            renderScale,
    int              floorStartPosition,
    AssetManager&    assetManager
);


/*
 * Function to update the current frame of a given animation based on a given
 * time between frames.
 */
void updateAnimationCurrentFrame(
    Animation& anim,
    float      deltaTime
);
