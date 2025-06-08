#pragma once

#include <glm/glm.hpp>

struct RectangleComponent {
    glm::vec3 position {0.0f};
    glm::vec2 size {0.0f};
};

struct TransformComponent {
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f); // Euler angles
    glm::vec3 scale = glm::vec3(1.0f);

    // glm::mat4 GetMatrix() const {
    //     glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
    //     glm::mat4 rot = glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);
    //     glm::mat4 scl = glm::scale(glm::mat4(1.0f), scale);
    //     return trans * rot * scl;
    // }

    // glm::mat4 GetViewMatrix() const {
    //     return glm::inverse(GetMatrix());
    // }
};
