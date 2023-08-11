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

VisibleObject::VisibleObject() {}

VisibleObject::VisibleObject(glm::vec3 position, glm::vec3 size, const std::string &asset) : rectangle(position, size, asset) {
    transform(position, size);
    rectangle.transform(position, size);
}

void VisibleObject::init() {

}

void VisibleObject::update() {

}

void VisibleObject::destroy() {
    rectangle.destroy();
}

std::unique_ptr<Mesh> &VisibleObject::getMesh() {
    return rectangle.getMesh();
}
