#pragma once

#include "rectangle.hpp"

#include <glm/glm.hpp>
#include <entt/entt.hpp>

struct GLFWwindow;

class ImGuiWrapper {
public:
    ImGuiWrapper(glm::vec2 viewport);

    void attach(GLFWwindow* window);
    void detach();

    void new_frame();
    void end_frame();

    void set(entt::registry& registry);
    void transform_box(int id, Rectangle& rectangle);

    void render();
    // void label(const std::string& text);

private:
    glm::vec2 viewport;
};
