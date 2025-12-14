#include "systems/render.hpp"

#include "mesh.hpp"
#include "rectangle.hpp"

void update_sprite(entt::registry& registry) {
    auto shader = get_asset_manager()->get_shader("main");
    shader->bind();

    registry.view<Mesh, entt::resource<Texture>, Rectangle>().each([shader](auto& mesh, auto& texture, auto& rectangle) {
    auto vertices = mesh_utils::generate_vertices(rectangle.get_position(), rectangle.get_size());
        shader->bind();
        mesh.bind(vertices);
        texture->bind();
    });
}
