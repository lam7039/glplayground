#pragma once

#include <glm/glm.hpp>

//TODO: separate components into their own files
struct CameraComponent {
    bool orthographic {true};
    glm::mat4 projection {1.0f};
    glm::mat4 view {1.0f};
};
