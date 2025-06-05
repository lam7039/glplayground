#include "entity.hpp"

void Entity::set_id(unsigned int id) {
    identifier = id;
}

void Entity::transform(glm::vec3& position, glm::vec3& size) {
    this->position = position;
    this->size = size;

    // shader->set_matrix("model", glm::mat4 {1.0f}); //TODO: per entity
}

void Entity::set_position(float x, float y, float z) {
    position = {x, y, z};
}

void Entity::set_size(float x, float y, float z) {
    size = {x, y, z};
}

unsigned int Entity::get_id() const {
    return identifier;
}

const glm::vec3& Entity::get_position() const {
    return position;
}

const glm::vec3& Entity::get_size() const {
    return size;
}
