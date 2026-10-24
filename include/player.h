#pragma once

#include "game_object.h"
#include <map>
#include "sprite_animation.h"
#include "sprite_renderer.h"

class Player : public GameObject
{
public:
    SpriteAnimator animator;
    glm::vec2 acceleration;
    glm::vec2 resistance;
    glm::vec2 maxVelocity = glm::vec2(1000.0f);
    SpriteAnimation idle;
    SpriteAnimation jump;
    SpriteAnimation fall;
    SpriteAnimation run;
    
    Player(glm::vec2 position, glm::vec2 size, Texture sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    Player();

    void Draw() override;
    void Update() override;
};