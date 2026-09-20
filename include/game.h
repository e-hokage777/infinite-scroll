#pragma once
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "logger.h"
#include "scene.h"

// TODO: see if you can make this a class member
void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// constants
const int WIDTH = 800;
const int HEIGHT = 600;

class Game
{
public:
    int width;
    int height;

    Game(int width = WIDTH, int height = HEIGHT) : width(width), height(height)
    {
        // setting up window
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // creating window and setting context
        this->window = glfwCreateWindow(WIDTH, HEIGHT, "game", NULL, NULL);
        if (window == NULL)
        {
            Logger::error("Failed to create GLFW window");
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(this->window, framebufferSizeCallback);

        // initializing glad
        if (!gladLoadGL(glfwGetProcAddress))
        {
            Logger::error("Failed to initialize GLAD");
            glfwTerminate();
        }

        // configurations
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void render(Scene scene)
    {
        while (!glfwWindowShouldClose(this->window))
        {
            glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // draw logic comes here
            scene.render();
            scene.draw();
            glfwSwapBuffers(this->window);
            glfwPollEvents();
        }
    }

private:
    GLFWwindow *window;
};