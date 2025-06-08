#include "renderer.hpp"

void Renderer::init() {
    api->init();
}

void Renderer::render_scene(const Scene& scene) {
    auto drawables = scene.get_renderables();
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
