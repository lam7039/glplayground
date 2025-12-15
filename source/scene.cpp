#include "scene.hpp"
#include "components/render.hpp"
#include "systems/camera.hpp"
#include "systems/render.hpp"

entt::entity create_sprite(entt::registry& registry, glm::vec3 position, glm::vec3 size, std::string_view texture) {
    Rectangle rectangle(position, size);
    auto vertices = mesh_utils::generate_vertices(rectangle.get_position(), rectangle.get_size());
    Mesh mesh(vertices, mesh_utils::generate_indices(vertices.size()));

    auto asset_manager = get_asset_manager();
    auto entity = registry.create();

    registry.emplace<Rectangle>(entity, rectangle);
    registry.emplace<Mesh>(entity, mesh);
    registry.emplace<entt::resource<Shader>>(entity, asset_manager->get_shader("main"));
    registry.emplace<entt::resource<Texture>>(entity, asset_manager->get_texture(texture));
    
    return entity;
}

entt::entity create_camera(entt::registry& registry, glm::vec3 position, glm::vec3 size) {
    Rectangle rectangle(position, size);

    auto asset_manager = get_asset_manager();
    auto camera = registry.create();

    registry.emplace<entt::resource<Shader>>(camera, asset_manager->get_shader("main"));
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
    update_camera(registry);
    update_sprite(registry);
}

void Scene::update() {
    update_sprite(registry);
}

void Scene::destroy() {
    registry.view<Mesh>().each([](auto& mesh) {
        mesh.destroy();
    });
    registry.clear();
}
