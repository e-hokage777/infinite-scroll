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

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

int main()
{


    Game game = Game(SCREEN_WIDTH, SCREEN_HEIGHT);

    Shader shader = Shader("shaders/main.vs", "shaders/main.fs");
    Shader spriteShader = Shader("shaders/sprite.vs", "shaders/sprite.fs");
    Plane plane = Plane(1.0f, 1.0f);
    Sprite sprite = Sprite("assets/shadow_dog.png", 10,12);

    // creating scene
    Scene scene = Scene(SCREEN_WIDTH, SCREEN_HEIGHT);
    // scene.add(&plane);
    scene.add({&sprite, spriteShader});
    game.add(&scene);
    game.render();

    return 0;
}