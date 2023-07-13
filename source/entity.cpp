#include "entity.hpp"

GameObject::GameObject() {
    position = {0.0f, 0.0f, 0.0f};
    // rectangle = new Quad(position, {1.0f}, textureId);
}

void GameObject::draw() {
    // rectangle.transform(position, size);
}

void GameObject::setPosition(float x, float y, float z) {
    position = {x, y, z};
}

glm::vec3 GameObject::getPosition() {
    return position;
}

void InterfaceObject::draw() {
    // rectangle.transform(position, size);
}
