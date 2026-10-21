#pragma once

#include "glad/gl.h"
#include "glm/gtc/matrix_transform.hpp"
#include "shader.h"
#include "resource_manager.h"
#include "texture.h"

class SpriteRenderer
{
private:
    static unsigned int VAO;
    static unsigned int VBO;
    static unsigned int EBO;
    static Shader shader;

public:
    // SpriteRenderer();
    // ~SpriteRenderer();

    static void Initialize();
    static void Draw(Texture sprite, glm::vec2 position, glm::vec2 scale, float rotate);
    static void Clip(glm::vec2 uvTopLeft, glm::vec2 uvBottomRight);
};