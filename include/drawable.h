#pragma once

#include "shader.h"
#include "glm/gtc/matrix_transform.hpp"

class Drawable{
    public:
    virtual void Draw(Shader shader) = 0;

    virtual ~Drawable() {}
};