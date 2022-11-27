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

struct Surface {
    SDL_Surface *surfaceSDL;
    vector2i size;
    bool hasAlpha;
    void *pixels;
};

class LibSDL {
    
public:
    void init();
    void quit();

    Window *createWindow(const std::string &title, vector2i size = vector2i(800, 500), vector2i position = vector2i(-1, -1));
    void swapWindow(Window *window);
    void destroyWindow(Window *window);

    Surface *loadSurface(const std::string &path) const;
    void freeSurface(Surface *surface);
};
