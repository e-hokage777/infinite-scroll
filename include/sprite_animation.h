#include <vector>
#include "glm/gtc/matrix_transform.hpp"
#include "texture.h"
#include <map>

class SpriteFrame
{
public:
    glm::vec2 uvTopLeft;
    glm::vec2 uvBottomRight;
    float duration;

    SpriteFrame(glm::vec2 uvTopLeft, glm::vec2 uvBottomRight, float duration);
};

class SpriteAnimation
{
public:
    std::string name;
    std::vector<SpriteFrame> frames;
    bool isLooping = true;

    float GetTotalDuration();
};

class SpriteAnimator
{
public:
    void Play(SpriteAnimation *animation);
    void Update(float deltaTime);
    SpriteFrame GetCurrentFrame();

private:
    SpriteAnimation *currentAnimation = nullptr;
    float currentTime = 0.0f;
    float playbackSpeed = 1.0f;
    int currentFrameIndex = 0;
};

// class Animation
// {
// public:
//     std::string name;
//     Texture texture;
//     std::vector<glm::vec2> frames;
//     float fps;

//     Animation(std::vector<glm::vec2> frames);
//     ~Animation();
// };

// class AnimationController
// {
// public:
//     std::string currentAnimation;
//     std::map<std::string, Animation> animations;
//     void setCurrentAnimation(std::string);
//     glm::vec2 getCurrentFrame();

//     AnimationController(std::map<std::string, Animation> animations);
//     ~AnimationController();
// };

// class Animator
// {
//     public:
//     AnimationController controller;
// };