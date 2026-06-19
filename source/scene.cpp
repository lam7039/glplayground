#include "scene.hpp"
#include "components/transform.hpp"
#include "components/camera.hpp"
#include "systems/camera.hpp"
#include "systems/render.hpp"

entt::entity create_sprite(entt::registry& registry, glm::vec3 position, glm::vec3 size, std::string_view texture) {
    TransformComponent transform;
    transform.position = position;
    transform.scale = size;

    auto vertices = mesh_utils::generate_vertices();
    Mesh mesh(vertices, mesh_utils::generate_indices(vertices.size()));

    auto asset_manager = get_asset_manager();
    auto entity = registry.create();

    registry.emplace<TransformComponent>(entity, transform);
    registry.emplace<Mesh>(entity, mesh);
    registry.emplace<entt::resource<Texture>>(entity, asset_manager->get_texture(texture));
    
    return entity;
}

entt::entity create_camera(entt::registry& registry, glm::vec3 position, glm::vec3 size) {
    TransformComponent transform;
    transform.position = position;
    transform.scale = size;

    auto asset_manager = get_asset_manager();
    auto camera = registry.create();

    registry.emplace<TransformComponent>(camera, transform);
    registry.emplace<CameraComponent>(camera);

    return camera;
}

Scene::Scene(const glm::vec2& viewport) {
    //TODO: load scene with a loader

    //TODO: render order
    auto camera = create_camera(registry, {0.0f, 0.0f, 0.0f}, {viewport, 0.0f});
    auto player = create_sprite(registry, {700.0f, 500.0f, 0.0f}, {100.0f, 150.0f, 1.0f}, "mario");
    auto background = create_sprite(registry, {0.0f, 0.0f, 0.0f}, {viewport, 1.0f}, "background");
}

void Scene::init() {
    
}

void Scene::update() {
    
}

void Scene::destroy() {
    registry.view<Mesh>().each([](auto& mesh) {
        mesh.destroy();
    });
    registry.clear();
}

entt::registry& Scene::get_registry() {
    return registry;
}
