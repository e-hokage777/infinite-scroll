#pragma once

#include <iostream>
#include <string>
#include "glad/gl.h"
#include "stb_image.h"
#include "shader.h"
#include "drawable.h"
#include "texture.h"
#include "resource_manager.h"

float accum = 0;

class Sprite : public Drawable
{
public:
    Texture texture;
    float width;
    float height;
    unsigned int state = 0;
    unsigned int states = 0;
    unsigned int maxFrames = 0;
    // unsigned int stateIndex = 0;
    unsigned int frameIndex = 0;
    unsigned int frames;
    float xOffset = 0.0f;
    float yOffset = 0.0f;
    float spriteWidth;
    float spriteHeight;

    Sprite() {};

    Sprite(float width, float height, std::string name, unsigned int states, unsigned int maxFrames)

    {
        this->width = width;
        this->height = height;
        this->states = states;
        this->maxFrames = maxFrames;
        this->spriteWidth = 1.0f / maxFrames;
        this->spriteHeight = 1.0f / states;
        // this->stateIndex = 0;
        this->frameIndex = 0;

        initializeSprite(name);
    }

    void Draw(Shader shader)
    {
        shader.use();
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
            // this->state = 0;
            this->frameIndex = (this->frameIndex + 1) % this->frames;
            this->xOffset = this->frameIndex * this->spriteWidth;
            this->yOffset = this->state * this->spriteHeight;
            accum = 0;
        }

        accum += deltaTime;
    }

    void setState(unsigned int state, unsigned int frames) {
        this->state = state;
        this->frames = frames;
    }

private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    void initializeSprite(std::string name)
    {
        // define texture
        // this->texture = Texture(path.c_str(), false);
        this->texture = ResourceManager::GetTexture(name);

        float positions[] = {
            0.0f, this->height, 0.0f,
            this->width, this->height, 0.0f,
            0.0f, 0.0f, 0.0f,
            this->width, 0.0f, 0.0f
        };

        float normals[] = {
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f
        };

        float texCoords[] = {
            this->xOffset, this->yOffset,
            this->xOffset + this->spriteWidth, this->yOffset,
            this->xOffset, this->yOffset + this->spriteHeight,
            this->xOffset + this->spriteWidth, this->yOffset + this->spriteHeight
        };


        int indices[] = {
            0, 1, 3,
            0, 2, 3};

        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);

        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(normals) + sizeof(texCoords), NULL, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(normals), normals);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(normals), sizeof(texCoords), texCoords);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)(sizeof(positions)));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *)(sizeof(positions) + sizeof(normals)));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
};