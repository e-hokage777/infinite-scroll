#include "sprite_animation.h"

SpriteFrame::SpriteFrame(glm::vec2 uvTopLeft, glm::vec2 uvBottomRight, float duration)
{
    this->uvTopLeft = uvTopLeft;
    this->uvBottomRight = uvBottomRight;
    this->duration = duration;
}

float SpriteAnimation::GetTotalDuration()
{
    float totalDuration = 0.0f;

    for (const auto &frame : frames)
    {
        totalDuration += frame.duration;
    }

    return totalDuration;
}

void SpriteAnimator::Play(SpriteAnimation *animation)
{
    if (currentAnimation == animation)
        return;

    currentAnimation = animation;
    currentTime = 0.0f;
    currentFrameIndex = 0;
}

void SpriteAnimator::Update(float deltaTime)
{
    currentTime += deltaTime * playbackSpeed;
    // std::cout << currentTime << std::endl;

    float totalAnimationDuration = currentAnimation->GetTotalDuration();

    if (currentTime > totalAnimationDuration)
    {
        if (currentAnimation->isLooping)
        {
            currentTime = fmod(currentTime, totalAnimationDuration);
        }
    }

    float accumulatedTime = 0.0f;
    for (unsigned int i = 0; i < currentAnimation->frames.size(); i++)
    {
        accumulatedTime += currentAnimation->frames[i].duration;
        if (currentTime <= accumulatedTime)
        {
            currentFrameIndex = i;
            break;
        }
    }
}

SpriteFrame SpriteAnimator::GetCurrentFrame()
{
    return currentAnimation->frames[currentFrameIndex];
}