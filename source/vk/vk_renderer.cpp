#include "vk/vk_renderer.hpp"

void VKRenderer::init() {
    
}

void VKRenderer::draw_mesh(const Mesh& mesh) {
    
}

void VKRenderer::draw_sprite(const Rectangle& sprite) {
    
}

void VKRenderer::draw(const Model& model) {
    
}

void VKRenderer::set_shader(Shader& shader) {
    shader.bind();
    shader.set_image("uTexture", 0);
    // shader.set_wireframe();
}

void VKRenderer::clear() {
    
}

void VKRenderer::clear_color(glm::vec4 color) {
    
}
