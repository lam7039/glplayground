#include "systems/camera.hpp"

#include "rectangle.hpp"
#include "components/render.hpp"
#include "asset_manager.hpp"

void update_camera(entt::registry& registry) {
    auto shader = get_asset_manager()->get_shader("main");
    shader->bind();

    registry.view<Rectangle, CameraComponent>().each([shader](auto& rectangle, auto& camera_component) {
        auto position = rectangle.get_position();
        auto size = rectangle.get_size();

        camera_component.projection = glm::ortho(position.x, position.x + size.x, position.y + size.y, position.y, 0.01f, 1000.0f);
        glm::vec3 negated_position = glm::vec3 {-position.x, -position.y, -1.0f};
        camera_component.view = glm::translate(glm::mat4 {1.0f}, negated_position);
    
        shader->set_matrix("view", camera_component.view);
        shader->set_matrix("projection", camera_component.projection);
    });
}
