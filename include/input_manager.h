#pragma once
#include "GLFW/glfw3.h"


class InputManager
{
public:
    static bool keys[1024];
    static void handleKeyInput(int key, int action);

    static bool isKeyDown(int key);
};