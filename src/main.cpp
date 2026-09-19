#include <iostream>
#include  "glad/gl.h"
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