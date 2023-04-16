#pragma once

#include <string>

class ImGuiWrapper {
public:
    void attach(void *window);
    void detach();
    void render();

    // void label(const std::string &text);
};
