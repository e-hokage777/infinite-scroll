#include "input_manager.h"

bool InputManager::keys[1024] = {};

void InputManager::handleKeyInput(int key, int action)
{
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }
}

bool InputManager::isKeyDown(int key)
{
    return keys[key];
}