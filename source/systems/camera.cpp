#include "systems/camera.hpp"
#include "components/camera.hpp"
#include "components/transform.hpp"

void CameraSystem::init() {
    
}

void CameraSystem::update(entt::registry& registry) {
    registry.view<TransformComponent, CameraComponent>().each([this](auto& transform, auto& camera_component) {
        auto position = transform.position;
        auto scale = transform.scale;

        camera_component.projection = glm::ortho(position.x, position.x + scale.x, position.y + scale.y, position.y, 0.01f, 1000.0f);
        glm::vec3 negated_position = glm::vec3 {-position.x, -position.y, -1.0f};
        camera_component.view = glm::translate(glm::mat4 {1.0f}, negated_position);
    });
}
