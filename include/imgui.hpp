#pragma once

#include "entity.hpp"

#include <glm/glm.hpp>

struct GLFWwindow;

class ImGuiWrapper {
public:
    ImGuiWrapper(glm::vec2 viewport);

    void attach(GLFWwindow *window);
    void detach();

    void newFrame();
    void endFrame();

    void set(std::vector<std::shared_ptr<DrawableEntity>> entities);
    void transformBox(std::shared_ptr<DrawableEntity> entity);

    void render();
    // void label(const std::string &text);

private:
    glm::vec2 viewport;
};
