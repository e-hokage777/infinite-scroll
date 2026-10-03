#include "plane.h"
#include "glad/gl.h"
#include <vector>

Plane::Plane(float x, float y, float z, float width, float height) : x(x), y(y), z(z), width(width), height(height)
{
    init();
}

void Plane::init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    std::vector<Vertex> vertices = {
        {{x, y, z}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{x + width, y, z}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{x, y + height, z}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
        {{x + width, y + height, z}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}};

    std::vector<unsigned int> indices = {
        0, 1, 3,
        0, 2, 3};

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Plane::Draw(Shader shader){
    shader.use();
    // glm::mat4 model = glm::mat4(1.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}