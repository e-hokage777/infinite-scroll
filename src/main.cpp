#pragma once

#include <vector>
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "logger.h"
#include "scene.h"
#include "input_manager.h"
#include "sprite.h"
#include "shader.h"
#include "player.h"

// TODO: see if you can make this a class member

// constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Game
{
public:
    InputManager inputManager;
    int width;
    int height;
    float deltaTime = 0;
    float lastFrame = 0;
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCREEN_WIDTH), 0.0f, static_cast<float>(SCREEN_HEIGHT), -1.0f, 1.0f);
    // Scene scene;
    Player player;

    Game(int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT) : width(width), height(height)
    {
        // initializing variables
        // setting up window
        glfwInit();
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        // creating window and setting context
        this->window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "game", NULL, NULL);
        if (window == NULL)
        {
            Logger::error("Failed to create GLFW window");
            glfwTerminate();
        }
        glfwSetWindowUserPointer(window, this);
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(this->window, Game::framebufferSizeCallback);
        glfwSetKeyCallback(this->window, Game::keyCallback);
        
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

        // attributes
        this->inputManager = InputManager();
        this->player = Player(0.0f, 0.0f);
        
        // configuring scene
        // scene = Scene(SCREEN_WIDTH, SCREEN_HEIGHT);
        Shader shader = Shader("shaders/main.vs", "shaders/main.fs");
    }
    
    void run()
    {
        Shader spriteShader = Shader("shaders/sprite.vs", "shaders/sprite.fs");
        Sprite sprite = Sprite(40.0f, 40.0f, "assets/shadow_dog.png", 10, 12);
        // scene.add({&sprite, spriteShader});

        while (!glfwWindowShouldClose(this->window))
        {
            deltaTime = (float)(glfwGetTime() - lastFrame);
            lastFrame = (float)(glfwGetTime());
            glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // draw logic comes here
            // for (auto scene : scenes)
            // {
            //     scene->update(deltaTime);
            //     scene->render();
            //     scene->draw();
            // }
            // sprite.Update(this->deltaTime);
            // sprite.Draw(spriteShader);
            this->update();
            this->render();
            glfwSwapBuffers(this->window);
            glfwPollEvents();
        }
    }


    void update()
    {
        this->player.update(this->deltaTime, &this->inputManager);
    }

    void render()
    {
        this->player.render(this->projection);
                
    }

private:
    GLFWwindow *window;
    // vector<Scene *> scenes;

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        Game *game = static_cast<Game *>(glfwGetWindowUserPointer(window));
        game->inputManager.handleKeyInput(key, action);
    }
};


int main(){
    Game game = Game();
    game.run();
    
    return 0;
}