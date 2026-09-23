#pragma once

#include <iostream>
#include <string>
#include "glad/gl.h"
#include "stb_image.h"
#include "shader.h"
#include "drawable.h"
#include "texture.h"

float accum = 0;

class Sprite : public Drawable
{
public:
    Texture texture;
    float width;
    float height;
    unsigned int states = 0;
    unsigned int maxFrames = 0;
    unsigned int stateIndex = 0;
    unsigned int frameIndex = 0;
    float xOffset = 0.0f;
    float yOffset = 0.0f;
    float spriteWidth;
    float spriteHeight;

    Sprite() {};

    Sprite(float width, float height, std::string path, unsigned int states, unsigned int maxFrames)

    {
        this->width = width;
        this->height = height;
        this->states = states;
        this->maxFrames = maxFrames;
        this->spriteWidth = 1.0f / maxFrames;
        this->spriteHeight = 1.0f / states;
        this->stateIndex = 0;
        this->frameIndex = 0;

        initializeSprite(path);
    }

    void Draw(Shader shader)
    {
        // this->update(0.0f);
        shader.use();
        // shader.uniformMat4("model", glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f));
        shader.setTexUnit(0, this->texture.ID, "sampler", GL_TEXTURE_2D);
        shader.setFloat("xOffset", this->xOffset);
        shader.setFloat("yOffset", this->yOffset);
        glBindVertexArray(this->VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Update(float deltaTime)
    {
        if (accum >= 1 / 24.0f)
        {
            this->stateIndex = 0;
            this->frameIndex = (this->frameIndex + 1) % 7;
            this->xOffset = this->frameIndex * this->spriteWidth;
            this->yOffset = this->stateIndex * this->spriteHeight;
            accum = 0;
        }

        accum += deltaTime;
    }

private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    void initializeSprite(std::string path)
    {
        // define texture
        this->texture = Texture(path.c_str(), false);

        float vertices[] = {
            // should should be vercies of a plane
            0.0f, this->height, 0.0f, 0.0f, 0.0f, 1.0f, this->xOffset, this->yOffset,                                        // top left
            this->width, this->height, 0.0f, 0.0f, 0.0f, 1.0f, this->xOffset + this->spriteWidth, this->yOffset,             // top right
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, this->xOffset, this->yOffset + this->spriteHeight,                           // bottom left
            this->width, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, this->xOffset + this->spriteWidth, this->yOffset + this->spriteHeight // bottom right
        };

        int indices[] = {
            0, 1, 3,
            0, 2, 3};

        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);

        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (sizeof(float) * 8), (void *)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (sizeof(float) * 8), (void *)(sizeof(float) * 3));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
};