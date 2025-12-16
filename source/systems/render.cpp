#include "systems/render.hpp"
#include "mesh.hpp"
#include "rectangle.hpp"

void RenderSystem::init(std::shared_ptr<AssetManager> asset_manager) {
    shader = asset_manager->get_shader("main");
    shader->bind();
}

void RenderSystem::update(entt::registry& registry) {
    registry.view<Mesh, entt::resource<Texture>, Rectangle>().each([this](auto& mesh, auto& texture, auto& rectangle) {
        if (!rectangle.is_dirty()) {
            return;
        }

        auto vertices = mesh_utils::generate_vertices(rectangle.get_position(), rectangle.get_size());

        //TODO: leave binding to the Renderer, pass renderer to the RenderSystem in the constructor
        shader->bind(); //TODO: should this be outside registry.view?
        mesh.bind(vertices);
        texture->bind();

        rectangle.clear_dirty();
    });
}
