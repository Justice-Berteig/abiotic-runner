/*
 * Implementation for Animation structure and other functions.
 */

#include "animation.hpp"
#include "assets.hpp"

#include "raylib.h"


Animation::Animation(Assets::Texture spriteSheet)
    : spriteSheet  (spriteSheet)
    , currentFrame (0)
    , totalFrames  (Assets::getFrameCountInTexture(spriteSheet))
    , lastFrameTime(0.0f)
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

    // Get rect for current frame.
    // Determine how many rows/cols of frames the spritesheet has.
    int ssCols{
          tex.width
        / static_cast<int>(Assets::getDimensionsForTexture(anim.spriteSheet).x)
    };
    // Determine row/col of current frame.
    int currentFrameRow{ anim.currentFrame / ssCols };
    int currentFrameCol{ anim.currentFrame % ssCols };
    // Rect for current frame is row/col * width/height.
    Rectangle frameRect{
        currentFrameCol * Assets::getDimensionsForTexture(anim.spriteSheet).x,
        currentFrameRow * Assets::getDimensionsForTexture(anim.spriteSheet).y,
        Assets::getDimensionsForTexture(anim.spriteSheet).x,
        Assets::getDimensionsForTexture(anim.spriteSheet).y
    };

    // Draw the frame.
    DrawTexturePro(
        tex,
        frameRect,
        {
            x * renderScale,
            (floorStartPosition - (y * renderScale)) - (32 * renderScale),
            Assets::getDimensionsForTexture(anim.spriteSheet).x * renderScale,
            Assets::getDimensionsForTexture(anim.spriteSheet).y * renderScale
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

    // Ensure current frame doesn't exceed the total number of frames.
    anim.currentFrame %= anim.totalFrames;
}
