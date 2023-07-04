#pragma once

#include <string>
#include "glm/glm.hpp"

class ImGuiWrapper {
public:
    void attach(void *window);
    void detach();

    void new_frame();
    void render(glm::vec3 &positionBackgroundTexture, glm::vec3 &positionMarioTexture);

    // void label(const std::string &text);
};
