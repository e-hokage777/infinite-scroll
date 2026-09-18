#pragma once

#include <vector>
#include "drawable.h"
#include "shader.h"
#include "glad/gl.h"
#include "logger.h"

// constants
int SCENE_WIDTH = 800;
int SCENE_HEIGHT = 600;

class Scene
{
public:
    unsigned int width;
    unsigned int height;
    std::vector<Drawable *> drawables = {};

    Scene(int width = WIDTH, int height = HEIGHT)
    {
        this->width = width;
        this->height = height;
    }

    void add(Drawable *drawable)
    {
        drawables.push_back(drawable);
    }

    void render(Shader shader)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (auto drawable : drawables)
        {
            drawable->Draw(shader);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void draw()
    {
        glBindVertexArray(this->VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

private:
    unsigned int framebuffer;
    unsigned int colorTexture;
    unsigned int depthStencilTexture;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    Shader shader;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    void init()
    {
        // creating framebuffer color texture
        glGenTextures(1, &this->colorTexture);
        glBindTexture(GL_TEXTURE_2D, this->colorTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_TEXTURE_2D, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);

        // creating depth buffer texture
        glGenTextures(1, &this->depthStencilTexture);
        glBindTexture(GL_TEXTURE_2D, this->depthStencilTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_STENCIL, this->width, this->height, 0, GL_DEPTH_STENCIL, GL_TEXTURE_2D, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);

        //// creating and initializing framebuffer
        glGenFramebuffers(1, &this->framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);

        // attaching depth-stencil texture
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->depthStencilTexture, 0);

        // attaching color texture
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->colorTexture, 0);

        // checking framebuffer status
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            Logger::error("ERROR::FRAMEBUFFER:: Render Framebuffer is not complete!");
        else
            Logger::info("SUCCESS: Render Framebuffer setup");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // setting up for drawing plane
        glCreateVertexArrays(1, &this->VAO);
        glCreateBuffers(1, &this->VBO);

        // setting up vertex buffer
        float vertices[] = {
            -1.0f,
            1.0f,
            0.0f,
            0.0f,
            1.0f, // top left
            1.0f,
            1.0f,
            0.0f,
            1.0f,
            1.0f, // top right
            1.0f,
            -1.0f,
            0.0f,
            1.0f,
            0.0f, // bottom right
            -1.0f,
            -1.0f,
            0.0f,
            0.0f,
            0.0f, // bottom left
        };
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // preparing indices
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0};
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        //// setting up VAO
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

        // Setting attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)(sizeof(float) * 3));
        glEnableVertexAttribArray(1);

        // ebo
        //TODO: check here well, might need to move data inside vao
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glBindVertexArray(0);

            // setting up shader
            this->shader = Shader("shaders/screen.vs", "shader/screen.fs");
    }
};