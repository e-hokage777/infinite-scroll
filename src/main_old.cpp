#include <iostream>
#include "glad/gl.h"
#include "GLFW/glfw3.h"
// #include "GLFW/glfw3.h"
#include "plane.h"
#include "sprite.h"
#include "scene.h"
#include "logger.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

Scene scene;
float deltaTime;
float lastFrame;

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    scene.resize(width, height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{

    // setting up window
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
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

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

    scene = Scene(SCREEN_WIDTH, SCREEN_HEIGHT);

    Shader shader = Shader("shaders/main.vs", "shaders/main.fs");
    Shader spriteShader = Shader("shaders/sprite.vs", "shaders/sprite.fs");
    Plane plane = Plane(1.0f, 1.0f);
    Sprite sprite = Sprite(40.0f, 40.0f,"assets/shadow_dog.png", 10, 12);
    scene.add({&sprite, spriteShader});

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        deltaTime = (float)(glfwGetTime() - lastFrame);
        lastFrame = (float)(glfwGetTime());
        glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.update(deltaTime);
        scene.render();
        scene.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}