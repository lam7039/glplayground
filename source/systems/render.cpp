#include "systems/render.hpp"
#include "mesh.hpp"
#include "rectangle.hpp"

RenderSystem::RenderSystem(Renderer& renderer) : renderer(renderer) {}

void RenderSystem::init(std::shared_ptr<AssetManager> asset_manager) {
    shader = asset_manager->get_shader("main");
    shader->bind();

    renderer.set_shader(shader);
}

void RenderSystem::update(entt::registry& registry) {
    registry.view<Mesh, Rectangle>().each([this](auto& mesh, auto& rectangle) {
        if (!rectangle.is_dirty()) {
            return;
        }

        auto vertices = mesh_utils::generate_vertices(rectangle.get_position(), rectangle.get_size());
        mesh.bind(vertices);

        rectangle.clear_dirty();
    });
}

void RenderSystem::render(entt::registry& registry) {
    renderer.clear_color();
    shader->bind();

    registry.view<Mesh, entt::resource<Texture>>().each([this](auto& mesh, auto& texture) {
        renderer.draw_mesh(mesh, texture);
    });
}
