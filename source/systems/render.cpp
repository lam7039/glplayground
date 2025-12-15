#include "systems/render.hpp"

#include "mesh.hpp"
#include "rectangle.hpp"

void update_sprite(entt::registry& registry) {
    registry.view<Mesh, entt::resource<Shader>, entt::resource<Texture>, Rectangle>().each([](auto& mesh, auto& shader, auto& texture, auto& rectangle) {
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
