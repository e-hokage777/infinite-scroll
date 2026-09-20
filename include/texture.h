#pragma once

#include "glad/gl.h"
#include "stb_image.h"
#include "logger.h"

class Texture
{
public:
    unsigned int ID;
    int width;
    int height;
    int nChannels;

    // default constructor
    Texture() {}
    Texture(const char *path, bool flip=true)
    {
        glGenTextures(1, &this->ID);
        glBindTexture(GL_TEXTURE_2D, this->ID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // loading texture data
        stbi_set_flip_vertically_on_load(flip);
        unsigned char *data = stbi_load(path, &this->width, &this->height, &this->nChannels, 0);

        unsigned int format = GL_RGB;

        if (this->nChannels == 4)
        {
            format = GL_RGBA;
        }

        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, format, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            Logger::error("Failed to load texture");
        }
        stbi_image_free(data);
    }
};