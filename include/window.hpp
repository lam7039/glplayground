#pragma once

#include "vector2.hpp"
#include <string>
#include <SDL2/SDL.h>

class Window {
    bool running {true};
    SDL_Window *instance;
    SDL_GLContext context;
public:
    vector2i position, size;
    
    Window(const std::string& title, vector2i size = vector2i(800, 500), vector2i position = vector2i(-1, -1));
    bool isRunning();
    void swap();
    void close();
    void quit();
};
