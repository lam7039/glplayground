#pragma once

#include <glm/glm.hpp>

struct GLFWwindow;

class ImGuiWrapper {
public:
    void attach(GLFWwindow *window);
    void detach();

    void newFrame();
    void endFrame();

    void set(glm::vec3 &positionTextureBackground, glm::vec3 &positionTextureMario, glm::vec3 &sizeTextureBackground, glm::vec3 &sizeTextureMario);
    void render();
    // void label(const std::string &text);
};
