#pragma once

#include <string>
#include <SDL2/SDL.h>

#include "draw.hpp"

class LibSDL {
public:
    void init();
    void quit();

    Window *createWindow(const std::string &title, vector2i size = vector2i(800, 500), vector2i position = vector2i(-1, -1));
    void **getOpenGLFuncName() const;
    void swapWindow(Window *window);
    void destroyWindow(Window *window);

    void pollEvents();
};

class ImageSDL {
public:
    static std::string workspace;

    void init();
    void quit();

    Surface *loadSurface(const std::string &path) const;
    void freeSurface(Surface *surface);
};
