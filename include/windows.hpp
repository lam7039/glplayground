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

    void add(std::string title, vector2i size = {1920, 1080}, vector2i position = {-1, -1});
    int windowCount();
    Window *find(unsigned int i);
    void remove();
    void quit();

    // bool running();
    void setCurrent(int windowId);
    void pollEvents(int windowId);
    void clearContext();
    void swap(int windowId);

    // void update();
    // void render();
};
