#include "renderer.hpp"

Renderer::Renderer(std::unique_ptr<GraphicsApiInterface> backend) : api(std::move(backend)) {

}

void Renderer::init() {
    api->init();
}

void Renderer::set_shader(Shader& shader) {
    api->set_shader(shader);
}

void Renderer::render(const DrawableMapAlias& drawables) {
    api->clear_color();
    for (auto& [id, drawable] : drawables) {
        api->draw_mesh(*drawable->get_mesh());
    }
}

void Renderer::clear() {
    api->clear();
}

void Renderer::destroy() {
    api.reset();
}
