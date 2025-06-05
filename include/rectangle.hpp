#pragma once

#include <glm/glm.hpp>

class Rectangle {
public:
    Rectangle(glm::vec3 position, glm::vec3 size);
    const glm::vec3 get_position() const;
    const glm::vec3 get_size() const;

    void transform(glm::vec3 position, glm::vec3 size);
private:
    glm::vec3 position;
    glm::vec3 size;
};

//TODO: use glm::vec2 for size
