#pragma once

#include <string>
#include "glm/glm.hpp"

class ImGuiWrapper {
public:
    void attach(void *window);
    void detach();

    void newFrame();
    void endFrame();

    void set(glm::vec3 &positionBackgroundTexture, glm::vec3 &positionMarioTexture);
    void render();
    // void label(const std::string &text);
};
