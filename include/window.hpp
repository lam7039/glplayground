#pragma once

#include "vector2.hpp"
#include <string>
#include <SDL2/SDL.h>

class Window {
    bool running {true};
    SDL_Window *instance;
    SDL_GLContext context;
public:
    vector2i pos, size;
    
    Window(const std::string& title, int width = 800, int height = 500, int x = -1, int y = -1);
    bool isRunning();
    void swap();
    void close();
    void quit();
};
