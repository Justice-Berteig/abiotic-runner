/*
 * Implementation for Animation structure and other functions.
 */

#include "animation.hpp"
#include "assets.hpp"

#include "raylib.h"


Animation::Animation(Assets::Texture spriteSheet)
    : spriteSheet      (spriteSheet)
    , animationFinished(false)
    , currentFrame     (0)
    , totalFrames      (Assets::getFrameCountInTexture(spriteSheet))
    , lastFrameTime    (0.0f)
{ }


void drawAnimationFrameAt(
    const Animation& anim,
    float            x,
    float            y,
    float            renderScale,
    int              floorStartPosition,
    AssetManager&    assetManager
) {
    // Get spritesheet.
    Texture2D tex{ assetManager.requestTexture(anim.spriteSheet) };

    // Get the dimensions for each frame of the spritesheet
    Vector2 frameDimensions{
        Assets::getDimensionsForTexture(anim.spriteSheet)
    };

    // Get rect for current frame.
    // Determine how many rows/cols of frames the spritesheet has.
    int ssCols{
          tex.width
        / static_cast<int>(frameDimensions.x)
    };
    // Determine row/col of current frame.
    int currentFrameRow{ anim.currentFrame / ssCols };
    int currentFrameCol{ anim.currentFrame % ssCols };
    // Rect for current frame is row/col * width/height.
    Rectangle frameRect{
        currentFrameCol * frameDimensions.x,
        currentFrameRow * frameDimensions.y,
        frameDimensions.x,
        frameDimensions.y
    };

    // Draw the frame.
    DrawTexturePro(
        tex,
        frameRect,
        {
            x * renderScale,
            (
                  floorStartPosition
                - (frameDimensions.y * renderScale)
                + (y * renderScale)
            ),
            frameDimensions.x * renderScale,
            frameDimensions.y * renderScale
        },
        {0, 0},
        0.0f,
        WHITE
    );
}


void updateAnimationCurrentFrame(
    Animation& anim,
    float      deltaTime
) {
    // Update the current frame based on given time.
    anim.lastFrameTime += deltaTime;
    while(anim.lastFrameTime >= anim.s_timeBetweenFrames) {
        anim.lastFrameTime -= anim.s_timeBetweenFrames;
        anim.currentFrame += 1;
    }

    if(anim.currentFrame >= anim.totalFrames) anim.animationFinished = true;

    // Ensure current frame doesn't exceed the total number of frames.
    anim.currentFrame %= anim.totalFrames;
}
