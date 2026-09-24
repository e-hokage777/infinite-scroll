#pragma once
#include "GLFW/glfw3.h"
class InputManager
{
public:
    void handleKeyInput(int key, int action)
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

    bool isKeyDown(int key)
    {
        return keys[key];
    }

private:
    bool keys[1024] = {false};
};