#include "entity.hpp"

GameObject::GameObject() {
    position = {0.0f, 0.0f, 0.0f};
}

void GameObject::draw() {
    quad.transform(position, size, textureId);
}

void GameObject::setPosition(float x, float y, float z) {
    position = {x, y, z};
}

glm::vec3 GameObject::getPosition() {
    return position;
}

void InterfaceObject::draw() {
    quad.transform(position, size, textureId);
}
