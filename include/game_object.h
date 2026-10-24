#pragma once
#include "glm/gtc/matrix_transform.hpp"
#include <string>
#include "shader.h"
#include "sprite_renderer.h"
#include "texture.h"

class GameObject
{
public:
    glm::vec2 position;
    float rotation;
    glm::vec2 size;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    glm::vec3 color;
    bool isSolid;
    bool isDestroyed;
    glm::mat4 modelMat;
    std::string name;
    Texture sprite;

    GameObject();
    GameObject(glm::vec2 position, glm::vec2 size, Texture sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec2 acceleration = glm::vec2(0.0f));
    virtual ~GameObject() = default;

    virtual void Draw();
    virtual void Update();
};