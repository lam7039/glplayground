#include "rectangle.hpp"

Rectangle::Rectangle(glm::vec3 position, glm::vec3 size) {
    this->position = position;
    this->size = size;
}

glm::vec3& Rectangle::get_position() {
    return position;
}

glm::vec3& Rectangle::get_size() {
    return size;
}

void Rectangle::transform(glm::vec3 position, glm::vec3 size) {
    this->position = position;
    this->size = size;
}

bool Rectangle::is_dirty() const {
    return dirty;
}

void Rectangle::set_dirty(bool dirty) {
    this->dirty = dirty;
}

void Rectangle::clear_dirty() {
    this->dirty = false;
}
