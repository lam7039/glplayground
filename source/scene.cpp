#include "scene.hpp"
#include "camera.hpp"
#include "rectangle.hpp"

#include <iostream>

entt::entity create_sprite(entt::registry& registry, glm::vec3 position, glm::vec3 size, const std::string& texture) {
    Rectangle rectangle(position, size);
    auto vertices = mesh_utils::generate_vertices(rectangle.get_position(), rectangle.get_size());
    Mesh mesh(vertices, mesh_utils::generate_indices(vertices.size()));

    auto texture_manager = get_asset_manager();
    auto entity = registry.create();
    registry.emplace<Rectangle>(entity, rectangle);
    registry.emplace<Mesh>(entity, mesh);
    registry.emplace<std::shared_ptr<Texture>>(entity, texture_manager->get_texture(texture).lock());
    
    return entity;
}

Scene::Scene(const glm::vec2& viewport) {
    //TODO: load scene with a loader

    //TODO: render order
    auto camera = registry.create();
    registry.emplace<Camera>(camera, viewport);

    auto player = create_sprite(registry, glm::vec3 {700.0f, 500.0f, 0.0f}, glm::vec3 {100.0f, 150.0f, 0.0f}, "mario");
    auto background = create_sprite(registry, glm::vec3 {0.0f, 0.0f, 0.0f}, glm::vec3 {viewport, 0.0f}, "background");
}

void Scene::init() {
    registry.view<Camera>().each([](auto& camera) {
        camera.init();
    });
    
    registry.view<Mesh, std::shared_ptr<Texture>>().each([](auto& mesh, auto& texture) {
        mesh.bind();
        texture->load();
    });
}

void Scene::update() {
    registry.view<Camera>().each([](auto& camera) {
        camera.update();
    });
}

void Scene::destroy() {
    registry.view<Mesh, std::shared_ptr<Texture>>().each([](auto& mesh, auto& texture) {
        texture->destroy();
        mesh.destroy();
    });
}
