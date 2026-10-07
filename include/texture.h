#pragma once

#include "glad/gl.h"
#include "stb_image.h"
#include "logger.h"

class Texture
{
public:
    unsigned int ID;
    int nChannels;
    unsigned int Internal_Format = GL_RGB; // potential for compile error
    unsigned int Image_Format = GL_RGB; // potential for compile error

    // default constructor
    Texture() {}

    void Generate(int width, int height, unsigned char *data)
    {
        glGenTextures(1, &this->ID);
        glBindTexture(GL_TEXTURE_2D, this->ID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, width, height, 0, Image_Format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};