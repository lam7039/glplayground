#include "renderer.hpp"

void Renderer::init(std::unique_ptr<IGraphicsApi> backend) {
    api = std::move(backend);
    api->init();
}

void Renderer::render(DrawableMapAlias drawables) {
    api->clear_color();
    for (auto [id, drawable] : drawables) {
        api->draw_mesh(drawable->get_mesh());
    }
}

void Renderer::clear() {
    api->clear();
}

void Renderer::destroy() {
    api.reset();
}
