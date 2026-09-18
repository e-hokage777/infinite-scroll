#pragma once
#include <iostream>

class Logger
{
public:
    static void info(const char *message) {}
    static void warning(const char *message) {}
    static void error(const char *message)
    {
        std::cout << message << std::endl;
    }
    static void debug(const char *message) {}
};