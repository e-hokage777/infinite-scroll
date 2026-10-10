#include "game.h"

void Game::Initialize()
{
    // loading textures
    ResourceManager::LoadTexture("assets/shadow_dog.png", true, "shadow_dog");
    ResourceManager::LoadTexture("assets/background/layer-1.png", true, "bg_layer_1");
    ResourceManager::LoadTexture("assets/background/layer-2.png", true, "bg_layer_2");
    ResourceManager::LoadTexture("assets/background/layer-3.png", true, "bg_layer_3");
    ResourceManager::LoadTexture("assets/background/layer-4.png", true, "bg_layer_4");
    ResourceManager::LoadTexture("assets/background/layer-5.png", true, "bg_layer_5");

    // loading shaders
    ResourceManager::LoadShader("basic.vs", "basic.fs", NULL, "basic");
    ResourceManager::LoadShader("sprite.vs", "sprite.fs", NULL, "sprite");
}

void Game::Update()
{
    for (auto &gameObject : gameObjects)
    {
        gameObject.Update();
    }
}

void Game::Render()
{
    for (auto &gameObject : gameObjects)
    {
        gameObject.Draw();
    }
}