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
    Shader spriteShader = Shader("shaders/sprite.vs", "shaders/sprite.fs");
    Plane plane = Plane(1.0f, 1.0f);
    Sprite sprite = Sprite("assets/shadow_dog.png", 10,12);

    // creating scene
    Scene scene = Scene();
    // scene.add(&plane);
    scene.add({&sprite, spriteShader});

    game.render(scene);

    return 0;
}