#include "renderer.hpp"
#include "texture.hpp"

void Renderer::init() {
    api->init();
}

void Renderer::render(entt::registry& registry) {
    //TODO: renderer shouldn't use ECS, do that in RenderSystem
    auto drawables = registry.view<Mesh, entt::resource<Texture>>();
    api->clear_color();

    drawables.each([this](auto& mesh, auto& texture) {
        mesh.bind();
        texture->bind();
        api->draw_mesh(mesh);
    });
}

void Renderer::destroy() {
    api.reset();
}

void Renderer::set_renderer(std::unique_ptr<GraphicsApiInterface> backend) {
    api = std::move(backend);
}

void Renderer::set_shader(Shader& shader) {
    api->set_shader(shader);
}

void Renderer::clear() {
    api->clear();
}
