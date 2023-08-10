#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec2 windowSize) {
    setPosition(0.0f, 0.0f, 1.0f);
    setSize(windowSize.x, windowSize.y, 1.0f);
}

void Camera::init() {
    shader = get_asset<Shader>("main");
    projection = glm::ortho(position.x, position.x + size.x, position.y, position.y + size.y, -1.0f, 1.0f);
    shader->setMatrix("mvp_matrix", projection);
}

void Camera::update() {
    shader->setMatrix("mvp_matrix", projection);
}

void Camera::setPosition(float x, float y, float z) {
    position = {x, y, z};
    projection = glm::ortho(x, x + size.x, y, y + size.y, -1.0f, 1.0f);
}

void Camera::setSize(float x, float y, float z) {
    size = {x, y, z};
    projection = glm::ortho(position.x, position.x + x, position.y, position.y + y, -1.0f, 1.0f);
}

glm::vec3 Camera::getPosition() {
    return position;
}
