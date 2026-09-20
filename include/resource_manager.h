#pragma once

#include "glad/gl.h"
#include "stb_image.h"
#include "logger.h"

class ResourceManager
{
public:
    static unsigned char * loadImage(const char *path)
    {
        stbi_set_flip_vertically_on_load(true);
        
    }
};