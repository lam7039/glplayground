#include "camera.hpp"
#include "asset_manager.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec2 viewport) {
    set_position(0.0f, 0.0f, 0.0f);
    set_size(viewport.x, viewport.y, 1.0f);
}

void Camera::init() {
    // projection = glm::ortho(position.x, position.x + size.x, position.y, position.y + size.y, -1.0f, 1.0f);
    shader = get_asset_manager().get_asset<Shader>("main");
    update();
}

void Camera::update() {
    set_position(position.x, position.y, position.z);
    set_size(size.x, size.y, size.z);
    shader->set_matrix("mvp_matrix", projection);
}

void Camera::destroy() {
    
}

void Camera::set_position(float x, float y, float z) {
    Entity::set_position(x, y, z);
    projection = glm::ortho(x, x + size.x, y, y + size.y, -1.0f, 1.0f);
}

void Camera::set_size(float x, float y, float z) {
    Entity::set_size(x, y, z);
    projection = glm::ortho(position.x, position.x + x, position.y, position.y + y, -1.0f, 1.0f);
}
