#pragma once

#include <glm/gtc/matrix_transform.hpp>

struct SpriteComponent {
    
};

struct CameraComponent {
    bool orthographic {true};
    glm::mat4 projection {1.0f};
    glm::mat4 view {1.0f};
};
