#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec2 viewport) {
    setPosition(0.0f, 0.0f, 0.0f);
    setSize(viewport.x, viewport.y, 1.0f);
}

void Camera::init() {
    // projection = glm::ortho(position.x, position.x + size.x, position.y, position.y + size.y, -1.0f, 1.0f);
    shader = get_asset<Shader>("main");
    update();
}

void Camera::update() {
    setPosition(position.x, position.y, position.z);
    setSize(size.x, size.y, size.z);
    shader->setMatrix("mvp_matrix", projection);
}

void Camera::destroy() {

}

void Camera::setPosition(float x, float y, float z) {
    Entity::setPosition(x, y, z);
    projection = glm::ortho(x, x + size.x, y, y + size.y, -1.0f, 1.0f);
}

void Camera::setSize(float x, float y, float z) {
    Entity::setSize(x, y, z);
    projection = glm::ortho(position.x, position.x + x, position.y, position.y + y, -1.0f, 1.0f);
}
