#pragma once

#include "window.hpp"

class ImGuiWrapper {
public:
    void attach(void *window);
    void detach();

    void newFrame();
    void endFrame();

    void set(glm::vec3 &positionTextureBackground, glm::vec3 &positionTextureMario, glm::vec3 &sizeTextureBackground, glm::vec3 &sizeTextureMario);
    void render();
    // void label(const std::string &text);
};
