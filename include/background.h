#pragma once
#include "plane.h"
#include "shader.h"
#include "glad/gl.h"

class Background : public GameObject {
public:
    float x, y, width, height;
    Shader shader;
    // glm::mat4 projection;
    Plane plane;
    Texture texture;

    explicit Background(){};

    explicit Background(float x, float y, float width, float height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->shader = Shader("shaders/basic.vs", "shaders/basic.fs");
        // projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), 0.0f, -2.0f);
        this->texture = Texture("assets/background/layer-4.png");
        plane = Plane(x, y, 0.0f, width, height);
    }


    void Draw(glm::mat4 projection) {
        glDepthMask(GL_FALSE);
        shader.use();
        shader.setTexUnit(0, texture.ID, "sampler", GL_TEXTURE_2D);
        shader.uniformMat4("projection", projection);
        plane.Draw(shader);
        glDepthMask(GL_TRUE);
    }
};