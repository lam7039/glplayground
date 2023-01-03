#pragma once

#include <vector>
#include <string>

#include "sdl.hpp"

class WindowManager {
    SDLlib sdllib;
    Context context;

    void **glFunc;
    std::vector<Window*> windows;
public:
    WindowManager();

    void add(std::string title, vector2i size = {800, 500}, vector2i position = {-1, -1});
    Window *find(unsigned int i);
    void remove();
    void quit();

    // bool running();
    void pollEvents();
    void clearContext();
    void swap();

    // void update();
    // void render();
};
