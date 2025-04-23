#include "entity.hpp"

void Entity::set_id(unsigned int id) {
    identifier = id;
}

void Entity::transform(glm::vec3 &position, glm::vec3 &size) {
    this->position = position;
    this->size = size;
}

void Entity::set_position(float x, float y, float z) {
    position = {x, y, z};
}

void Entity::set_size(float x, float y, float z) {
    size = {x, y, z};
}

unsigned int &Entity::getId() {
    return identifier;
}

glm::vec3 &Entity::getPosition() {
    return position;
}

glm::vec3 &Entity::getSize() {
    return size;
}

// void Entity::init() {
//     // rectangle.transform(position, size);
// }

// void Entity::update() {
//     // rectangle.transform(position, size);
// }

// void Entity::destroy() {
//     // rectangle.destroy();
// }

// Mesh &Entity::getMesh() {
//     return *rectangle.getMesh();
// }
