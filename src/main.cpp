#pragma once

#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "logger.h"
#include "game.h"
#include "timer.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // creating window and setting context
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "game", NULL, NULL);
    if (window == NULL)
    {
        Logger::error("Failed to create GLFW window");
        glfwTerminate();
    }
    // glfwSetWindowUserPointer(window, this);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    // glfwSetKeyCallback(this->window, Game::keyCallback);

    // initializing glad
    if (!gladLoadGL(glfwGetProcAddress))
    {
        Logger::error("Failed to initialize GLAD");
        glfwTerminate();
    }

    // configurations
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //
    Game::Initialize();

    float lastTime = 0;
    float deltaTime = 0;
    float currentTime = 0;
    while (!glfwWindowShouldClose(window))
    {
        currentTime = float(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        Time::deltaTime = deltaTime;
        Game::Update();
        Game::Render();
    }

    return 0;
}