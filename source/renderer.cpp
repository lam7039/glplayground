#include "renderer.hpp"

void Renderer::init() {
    api->init();
}

void Renderer::render(const DrawableMapAlias& drawables) {
    api->clear_color();
    for (auto& [id, drawable] : drawables) {
        api->draw_mesh(*drawable->get_mesh());
    }
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
