#pragma once
#include "player.h"
#include "timer.h"

Player::Player(glm::vec2 position, glm::vec2 size, Texture sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f)) : GameObject(position, size, sprite, color, velocity)
{

    // creating animations
    // idle
    idle = SpriteAnimation();
    jump = SpriteAnimation();
    fall = SpriteAnimation();
    run = SpriteAnimation();

    animator = SpriteAnimator();
    animator.Play(&idle);

    // filling in frames
    float numStates = 10;
    float maxFrames = 12;
    float dy = 1 / numStates;
    float dx = 1 / maxFrames;

    unsigned int stateMaxFrames[] = {7, 7, 7, 9};
    for (size_t i = 0; i < sizeof(stateMaxFrames) / sizeof(unsigned int); ++i)
    {
        for (size_t j = 0; j < stateMaxFrames[i]; ++j)
        {
            if (i == 0)
            {
                idle.frames.push_back(SpriteFrame(
                    glm::vec2(dx * j, 1 - dy * i),
                    glm::vec2(dx * j + dx, 1 - (dy*i) - dy),
                    0.1f));
            }
        }
    }
}

Player::Player() : Player(
                       glm::vec2(0.0f),
                       glm::vec2(1.0f),
                       Texture(),
                       glm::vec3(1.0f),
                       glm::vec2(0.0f)) {}

void Player::Update()
{
    GameObject::Update();
    animator.Update(Time::deltaTime);
}

void Player::Draw()
{

    // SpriteRenderer::Clip(animator.currentAnimation)
    SpriteFrame currentFrame = animator.GetCurrentFrame();
    SpriteRenderer::Clip(currentFrame.uvTopLeft, currentFrame.uvBottomRight);
    GameObject::Draw();
    SpriteRenderer::Clip(glm::vec2(0.0f), glm::vec3(1.0f));
}