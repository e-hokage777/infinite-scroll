#include "game.h"
#include "sprite_renderer.h"

// variable definitions
std::vector<GameObject *> Game::gameObjects;

void Game::Initialize()
{

    // loading textures
    ResourceManager::LoadTexture("assets/shadow_dog.png", true, "shadow_dog");
    ResourceManager::LoadTexture("assets/background/layer-1.png", false, "bg_layer_1");
    ResourceManager::LoadTexture("assets/background/layer-2.png", true, "bg_layer_2");
    ResourceManager::LoadTexture("assets/background/layer-3.png", true, "bg_layer_3");
    ResourceManager::LoadTexture("assets/background/layer-4.png", true, "bg_layer_4");
    ResourceManager::LoadTexture("assets/background/layer-5.png", true, "bg_layer_5");

    // loading shaders
    ResourceManager::LoadShader("shaders/basic.vs", "shaders/basic.fs", nullptr, "basic");
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.fs", nullptr, "sprite");


    // initializing
    SpriteRenderer::Initialize();
}

void Game::Update()
{
    for (auto &gameObject : gameObjects)
    {
        gameObject->Update();
    }
}

void Game::Render()
{
    for (auto &gameObject : gameObjects)
    {
        gameObject->Draw();
    }
}

void Game::AddGameObject(GameObject *gameObject)
{
    gameObjects.push_back(gameObject);
}