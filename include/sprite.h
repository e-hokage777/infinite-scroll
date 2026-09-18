#pragma once

#include <iostream>
#include <string>
#include "glad/gl.h"
#include "stb_image.h"
#include "shader.h"
#include "plane.h"
#include "drawable.h"

class Sprite: public Drawable
{
public:
    unsigned int texture = 0;
    unsigned int states = 0;
    unsigned int maxFrames = 0;
    unsigned int stateIndex = 0;
    unsigned int frameIndex = 0;
    Plane plane;

    Sprite(std::string path, unsigned int states)
        : plane(1.0f, 1.0f)
    {
        this->states = states;
        initializeSprite(path);
        this->stateIndex = 0;
        this->frameIndex = 0;
        this->maxFrames = 0;
    }

    void Draw(Shader shader)
    {
        shader.use();
        shader.setTexUnit(0, this->texture, "spriteSampler", GL_TEXTURE_2D);
        this->plane.Draw(shader);
    }

private:
    void initializeSprite(std::string path)
    {
        // loading image
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);


        if (data == nullptr)
        {
            std::cout << "Failed to load texture: " << path << std::endl;
            return;
        }


        GLenum format = GL_RGB;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        // creating the texture
        glGenTextures(1, &this->texture);
        glBindTexture(GL_TEXTURE_2D, this->texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);
    }
};