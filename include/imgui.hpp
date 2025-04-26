#pragma once

#include "entity.hpp"

#include <glm/glm.hpp>

struct GLFWwindow;

class ImGuiWrapper {
public:
    ImGuiWrapper(glm::vec2 viewport);

    void attach(GLFWwindow *window);
    void detach();

    void new_frame();
    void end_frame();

    void set(std::vector<std::shared_ptr<Entity>> entities);
    void transform_box(std::shared_ptr<Entity>& entity);

    void render();
    // void label(const std::string &text);

private:
    glm::vec2 viewport;
};
