#pragma once

#include <vector>
#include <string>

#include "sdl.hpp"
#include "draw.hpp"

class Windows {
    void **glFuncName;
    std::string workspace;
    std::vector<Window*> windows;
public:
    LibSDL sdllib;
    ImageSDL sdlimage;
    Context context;

    Windows();

    void add(std::string title, vector2i size = vector2i(800, 500), vector2i position = vector2i(-1, -1));
    void remove();
    void quit();

    void update();
    void render();
};
