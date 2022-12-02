#pragma once

#include <string>
#include <functional>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "vector2.hpp"

typedef void (*GL_PROC)(unsigned int);

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
    GL_PROC getProc() const;
    void swapWindow(Window *window);
    void destroyWindow(Window *window);

    Surface *loadSurface(const std::string &path) const;
    void freeSurface(Surface *surface);

    std::string workspace() const;
};
