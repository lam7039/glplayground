#include "camera.hpp"
#include "asset_manager.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec2 viewport) {
    set_size(viewport.x, viewport.y, 1.0f);
}

void Camera::init() {
    shader = get_asset_manager()->get_shader("main");
    update();
}

void Camera::update() {
    projection = glm::ortho(position.x, position.x + size.x, position.y, position.y + size.y, -1.0f, 1.0f);
    shader->set_matrix("mvp_matrix", projection);
}

void Camera::destroy() {
    
}
