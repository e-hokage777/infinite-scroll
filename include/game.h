#pragma once

#include <vector>
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"

class Game
{

public:
    // methods
    static void Initialize() {}
    static void Update() {}
    static void Render() {}

private:
    // attributes
    static std::vector<GameObject> gameObjects;
};