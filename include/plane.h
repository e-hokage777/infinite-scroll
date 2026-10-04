#pragma once

#include "shader.h"
class Plane
{
public:
    float x;
    float y;
    float z;
    float width;
    float height;

    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };

    explicit Plane() {};

    explicit Plane(float x, float y, float z, float width, float height);

    void Draw(Shader shader);

private:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;

    void init();
};