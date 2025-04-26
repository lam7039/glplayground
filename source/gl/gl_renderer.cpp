#include "gl/gl_renderer.hpp"
#include "gl/gl.hpp"

#include "shader.hpp"
#include "texture.hpp"

void GLRenderer::init() {
    // CHECK_GL_ERROR(glEnable(GL_DEPTH_TEST));
    // CHECK_GL_ERROR(glDepthFunc(GL_LEQUAL));
    CHECK_GL_ERROR(glEnable(GL_BLEND));
    CHECK_GL_ERROR(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    // CHECK_GL_ERROR(glEnable(GL_SCISSOR_TEST));

    clear_color();
    clear();

    asset_manager = get_asset_manager();
    std::shared_ptr<Shader> shader = asset_manager->get_shader("main");
    shader->bind();
    shader->set_image("ourTexture", 0);
    // shader->set_wireframe();
}

void GLRenderer::draw_mesh(const Mesh& mesh) {
    asset_manager->get_texture(mesh.get_texture())->bind();
    mesh.input_layout_bind();
    CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, mesh.get_index_count(), GL_UNSIGNED_INT, nullptr));
    mesh.input_layout_unbind();
}

//TODO: replace rectangle with a Sprite class
void GLRenderer::draw_sprite(const Rectangle& sprite) {
    //TODO: this is copied from draw_mesh
    // asset_manager->get_texture(sprite->get_texture())->bind();
    // sprite->input_layout_bind();
    // CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, mesh->get_index_count(), GL_UNSIGNED_INT, nullptr));
    // sprite->input_layout_unbind();
}

void GLRenderer::draw(const Model& model) {
    for (auto& mesh : model.get_meshes()) {
        draw_mesh(*mesh);
    }
}

void GLRenderer::clear() {
    CHECK_GL_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void GLRenderer::clear_color(glm::vec4 color) {
    CHECK_GL_ERROR(glClearColor(color.x, color.y, color.z, color.a));
}
