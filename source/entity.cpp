#include "entity.hpp"

void Entity::transform(glm::vec3 &position, glm::vec3 &size) {
    this->position = position;
    this->size = size;
}

void Entity::setPosition(float x, float y, float z) {
    position = {x, y, z};
}

void Entity::setSize(float x, float y, float z) {
    size = {x, y, z};
}

glm::vec3 &Entity::getPosition() {
    return position;
}

glm::vec3 &Entity::getSize() {
    return size;
}

DrawableEntity::DrawableEntity() {}

DrawableEntity::DrawableEntity(glm::vec3 position, glm::vec3 size, const std::string &asset) : rectangle(position, size, asset) {
    transform(position, size);
    rectangle.transform(position, size);
}

void DrawableEntity::init() {

}

void DrawableEntity::update() {
    rectangle.transform(position, size);
}

void DrawableEntity::destroy() {
    rectangle.destroy();
}

std::unique_ptr<Mesh> &DrawableEntity::getMesh() {
    return rectangle.getMesh();
}
