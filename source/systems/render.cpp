#include "systems/render.hpp"

#include "mesh.hpp"
#include "rectangle.hpp"

//TODO: use RenderSystem instead of function
RenderSystem::RenderSystem(entt::registry& registry) : registry(registry) {
    shader = get_asset_manager()->get_shader("main");
    shader->bind();
}

void RenderSystem::update() {
    registry.view<Mesh, entt::resource<Texture>, Rectangle>().each([this](auto& mesh, auto& texture, auto& rectangle) {
        if (! rectangle.is_dirty()) {
            return;
        }

        auto vertices = mesh_utils::generate_vertices(rectangle.get_position(), rectangle.get_size());
        shader->bind();
        mesh.bind(vertices);
        texture->bind();

        rectangle.clear_dirty();
    });
}

void update_sprite(entt::registry& registry) {
    auto shader = get_asset_manager()->get_shader("main");
    shader->bind();

    registry.view<Mesh, entt::resource<Texture>, Rectangle>().each([shader](auto& mesh, auto& texture, auto& rectangle) {
        if (! rectangle.is_dirty()) {
            return;
        }

        auto vertices = mesh_utils::generate_vertices(rectangle.get_position(), rectangle.get_size());
        shader->bind();
        mesh.bind(vertices);
        texture->bind();

        rectangle.clear_dirty();
    });
}
