#include "sprite_renderer.h"

unsigned int SpriteRenderer::VAO;
unsigned int SpriteRenderer::VBO;
unsigned int SpriteRenderer::EBO;
Shader SpriteRenderer::shader;

void SpriteRenderer::Initialize()
{
    // defining vertices and indices
    float positions[] = {
        0.0f, 1.0f, 0.0f, // top left
        1.0f, 1.0f, 0.0f, // top right
        1.0f, 0.0f, 0.0f, // bottom right
        0.0f, 0.0f, 0.0f  // bottom left
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
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // creating buffers
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(normals) + sizeof(texCoords), NULL, GL_DYNAMIC_DRAW);

    // moving data to array buffer
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(normals), normals);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(normals), sizeof(texCoords), texCoords);

    // setting attribute pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)(sizeof(positions)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *)(sizeof(positions) + sizeof(normals)));

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // setting up shader
    shader = ResourceManager::GetShader("sprite");
}

void SpriteRenderer::Draw(Texture sprite, glm::vec2 position, glm::vec2 size, float rotate)
{
    shader.use();

    shader.setTexUnit(0, sprite.ID, "sampler", GL_TEXTURE_2D);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f)); // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));   // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));  // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back // move origin of rotation to center of quad
    
    // model = glm::translate(model, glm::vec3(0.5f * abs(size.x), 0.5f * size.y, 0.0f));   // move origin of rotation to center of quad
    model = glm::scale(model, glm::vec3(size, 1.0f));
    // model = glm::translate(model, glm::vec3(-0.5f * abs(size.x), -0.5f * size.y, 0.0f)); // move origin back // move origin of rotation to center of quad

    shader.uniformMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::Clip(glm::vec2 uvTopLeft = glm::vec2(0.0f, 1.0f), glm::vec2 uvBottomRight = glm::vec2(1.0f, 0.0f))
{
    shader.uniformVec2("uvTopLeft", uvTopLeft);
    shader.uniformVec2("uvBottomRight", uvBottomRight);
}