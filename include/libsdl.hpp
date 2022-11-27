#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "vector2.hpp"

struct Window {
    bool running {false};
    vector2i position, size;
    SDL_Window *instance;
    SDL_GLContext context;
};

class LibSDL {
    
public:
    void init();
    void quit();

    Window *createWindow(const std::string &title, vector2i size = vector2i(800, 500), vector2i position = vector2i(-1, -1));
    void swapWindow(Window *window);
    void closeWindow(Window *window);
    void deleteWindow(Window *window);

    SDL_Surface *loadSurface(const std::string &path) const;
    void freeSurface(SDL_Surface *surface);
};
