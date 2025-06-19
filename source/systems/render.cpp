#include "systems/render.hpp"

#include "asset_manager.hpp"
#include "mesh.hpp"

void update_sprite(entt::registry& registry) {
    auto shader = get_asset_manager()->get_shader("main");
    shader->bind();

    registry.view<Mesh, entt::resource<Texture>>().each([shader](auto& mesh, auto& texture) {
        shader->bind();
        mesh.bind();
        texture->bind();
    });
}
