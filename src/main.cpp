#include <iostream>
#include "glad/gl.h"
#include "GLFW/glfw3.h"
// #include "GLFW/glfw3.h"
#include "plane.h"
#include "sprite.h"
#include "game.h"
#include "scene.h"
// void frameBufferCallback(GLFWwindow *window, int width, int height)
// {
//     glViewport(0, 0, width, height);
// }

int main()
{

    // initializing glad

    // glfwInit();

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    // if (window == NULL)
    // {
    //     std::cout << "Failed to create GLFW window" << std::endl;
    //     glfwTerminate();
    //     return -1;
    // }

    // glfwMakeContextCurrent(window);
    // glfwSetFramebufferSizeCallback(window, frameBufferCallback);

    // if (!gladLoadGL(glfwGetProcAddress))
    // {
    //     std::cout << "Failed to initialize GLAD" << std::endl;
    //     return -1;
    // }
    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Game game = Game();

    Shader shader = Shader("shaders/main.vs", "shaders/main.fs");
    Plane plane = Plane(1.0f, 1.0f);
    Sprite sprite = Sprite("assets/shadow_dog.png", 4);

    // creating scene
    Scene scene = Scene();
    // scene.add(&plane);
    scene.add(&sprite);

    // while (!glfwWindowShouldClose(window))
    // {
    //     glClearColor(0.0f, 0.5f, 0.0f, 1.0f);
    //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //     shader.use();

    //     sprite.draw(shader);

    //     glfwPollEvents();
    //     glfwSwapBuffers(window);
    // }

    game.render(scene, shader);

    return 0;
}