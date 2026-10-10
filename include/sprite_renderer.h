#pragma once

#include "glad/gl.h"
#include "shader.h"

class SpriteRenderer
{
private:
    static unsigned int VAO;
    static unsigned int VBO;
    static unsigned int EBO;

public:
    SpriteRenderer() {}
    ~SpriteRenderer() {}

    static void initialize() {}
    static void Draw(Shader &shader){}
};