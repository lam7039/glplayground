#include "rectangle.hpp"

Rectangle::Rectangle(glm::vec3 position, glm::vec3 size) {
    this->position = position;
    this->size = size;
}

const glm::vec3 Rectangle::get_position() const {
    return position;
}

const glm::vec3 Rectangle::get_size() const {
    return size;
}

void Rectangle::transform(glm::vec3 position, glm::vec3 size) {
    this->position = position;
    this->size = size;
}
