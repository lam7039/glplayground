#pragma once

#include <string>
#include <functional>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "vector2.hpp"

struct Window {
    bool running {false};
    vector2i position, size;
    void **window {nullptr};
    void *context {nullptr};
};

struct Surface {
    void *surface;
    vector2i size;
    bool hasAlpha;
    void *pixels;
};

class LibSDL {
    
public:
    std::string workspace;
    void init();
    void quit();

    Window *createWindow(const std::string &title, vector2i size = vector2i(800, 500), vector2i position = vector2i(-1, -1));
    void **getProc() const;
    void swapWindow(Window *window);
    void destroyWindow(Window *window);

    Surface *loadSurface(const std::string &path) const;
    void freeSurface(Surface *surface);
};
