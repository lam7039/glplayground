#include "systems/render.hpp"
#include "mesh.hpp"
#include "components/render.hpp"
#include "components/transform.hpp"

RenderSystem::RenderSystem(Renderer& renderer) : renderer(renderer) {}

//TODO: don't pass the entire asset manager to the system, instead let the renderer own the shader and let the system request rendering with IDs or pipelines, something like: renderer.use_pipeline("main");
void RenderSystem::init(std::shared_ptr<AssetManager> asset_manager) {
    shader = asset_manager->get_shader("main");
    renderer.set_shader(shader);
}

void RenderSystem::render(entt::registry& registry) {
    auto camera = *registry.view<CameraComponent>().begin();
    const auto& active_camera = registry.get<CameraComponent>(camera);

    renderer.clear_color();

    shader->bind();
    shader->set_matrix("projection", active_camera.projection);
    shader->set_matrix("view", active_camera.view);

    registry.view<Mesh, TransformComponent, entt::resource<Texture>>().each([this](auto& mesh, auto& transform, auto& texture) {
        shader->set_matrix("model", transform.matrix());

        renderer.draw_mesh(mesh, texture);
    });
}
