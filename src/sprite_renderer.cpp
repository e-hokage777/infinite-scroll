#include "sprite_renderer.h"

void SpriteRenderer::initialize()
{
    // defining vertices and indices
    float positions[] = {
        -1.0f, 1.0f, 0.0f, // top left
        1.0f, 1.0f, 0.0f,  // top right
        1.0f, -1.0f, 0.0f, // bottom right
        -1.0f, -1.0f       // bottom left
    };

    float normals[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f};

    float texCoords[] = {
        0.0f, 1.0f, // top left
        1.0f, 1.0f, // top right
        1.0f, 0.0f, // bottom right
        0.0f, 0.0f  // bottom left
    };

    unsigned int indices[] = {
        0, 3, 2,
        0, 2, 1};

    // setting up vertex array
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // creating buffers
    glCreateBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(normals) + sizeof(texCoords), NULL, GL_DYNAMIC_DRAW);

    // moving data to array buffer
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(normals), normals);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(normals), sizeof(texCoords), texCoords);

    // setting attribute pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3 * sizeof(float), GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3 * sizeof(float), GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)(sizeof(positions) / sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2 * sizeof(float), GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *)((sizeof(positions) + sizeof(normals)) / sizeof(float)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SpriteRenderer::Draw(Shader &shader)
{
    shader.use();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}