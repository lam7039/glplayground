#pragma once

#include <string>

#include "draw.hpp"

class SDLlib {
public:
    void init();
    void quit();

    Window *createWindow(const std::string &title, vector2i size = {800, 500}, vector2i position = {-1, -1});
    void setCurrent(Window *window);
    void **getOpenGLFunc() const;
    void swapWindow(Window *window);
    void destroyWindow(Window *window);

    void pollEvents(Window *window);
};

class SDLimage {
public:
    static std::string workspace;

    void init();
    void quit();
    Surface *loadSurface(const std::string &path) const;
    void freeSurface(Surface *surface);
};
