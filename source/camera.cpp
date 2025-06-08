#include "camera.hpp"
#include "asset_manager.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec2 viewport) {
    set_size(viewport.x, viewport.y, 1.0f);
}

void Camera::init() {
    
}

void Camera::update() {
    //TODO: return view/projection/model and separate shader from camera
    auto shader = get_asset_manager()->get_shader("main");

    projection = glm::ortho(0.0f, size.x, size.y, 0.0f, 0.01f, 1000.0f);
    glm::vec3 negated_position = glm::vec3 {-position.x, -position.y, -1.0f};
    view = glm::translate(glm::mat4 {1.0f}, negated_position);

    shader->set_matrix("view", view);
    shader->set_matrix("projection", projection);
}

void Camera::destroy() {
    
}
