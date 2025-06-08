#include "scene.hpp"

#include <glm/gtc/matrix_transform.hpp>

entt::entity create_sprite(entt::registry& registry, glm::vec3 position, glm::vec3 size, const std::string& texture) {
    Rectangle rectangle(position, size);
    auto vertices = mesh_utils::generate_vertices(rectangle.get_position(), rectangle.get_size());
    Mesh mesh(vertices, mesh_utils::generate_indices(vertices.size()));

    auto texture_manager = get_asset_manager();
    auto entity = registry.create();
    registry.emplace<Rectangle>(entity, rectangle);
    registry.emplace<Mesh>(entity, mesh);
    registry.emplace<entt::resource<Texture>>(entity, texture_manager->get_texture(texture));
    
    return entity;
}

struct CameraComponent {
    bool orthographic {true};
    glm::mat4 projection {1.0f};
    glm::mat4 view {1.0f};
};

entt::entity create_camera(entt::registry& registry, glm::vec3 position, glm::vec3 size) {
    Rectangle rectangle(position, size);

    auto camera = registry.create();
    registry.emplace<Rectangle>(camera, rectangle);
    registry.emplace<CameraComponent>(camera);

    return camera;
}

Scene::Scene(const glm::vec2& viewport) {
    //TODO: load scene with a loader

    //TODO: render order
    auto camera = create_camera(registry, {0.0f, 0.0f, 0.0f}, {viewport, 0.0f});
    auto player = create_sprite(registry, {700.0f, 500.0f, 0.0f}, {100.0f, 150.0f, 0.0f}, "mario");
    auto background = create_sprite(registry, {0.0f, 0.0f, 0.0f}, {viewport, 0.0f}, "background");
}

void Scene::init() {
    registry.view<Mesh, entt::resource<Texture>>().each([](auto& mesh, auto& texture) {
        mesh.bind();
        texture->bind();
    });
}

void Scene::update() {
    registry.view<Rectangle, CameraComponent>().each([](auto& rectangle, auto& camera_component) {
        auto shader = get_asset_manager()->get_shader("main");
        auto position = rectangle.get_position();
        auto size = rectangle.get_size();

        camera_component.projection = glm::ortho(position.x, position.x + size.x, position.y + size.y, position.y, 0.01f, 1000.0f);
        glm::vec3 negated_position = glm::vec3 {-position.x, -position.y, -1.0f};
        camera_component.view = glm::translate(glm::mat4 {1.0f}, negated_position);
    
        shader->set_matrix("view", camera_component.view);
        shader->set_matrix("projection", camera_component.projection);
    });
}

void Scene::destroy() {
    registry.view<Mesh>().each([](auto& mesh) {
        mesh.destroy();
    });
}
