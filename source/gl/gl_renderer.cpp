#include "gl/gl_renderer.hpp"
#include "gl/gl.hpp"
#include "assets.hpp"

void GLRenderer::init() {
    // CHECK_GL_ERROR(glEnable(GL_DEPTH_TEST));
    // CHECK_GL_ERROR(glDepthFunc(GL_LEQUAL));
    CHECK_GL_ERROR(glEnable(GL_BLEND));
    CHECK_GL_ERROR(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    // CHECK_GL_ERROR(glEnable(GL_SCISSOR_TEST));

    clear_color();
    clear();

    std::shared_ptr<Shader> shader = Global::get_asset<Shader>("main");
    shader->bind();
    shader->set_image("ourTexture", 0);
    // shader->set_wireframe();
}

void GLRenderer::draw_mesh(const std::shared_ptr<Mesh>& mesh) {
    Global::get_asset<Texture>(mesh->get_texture())->bind();
    mesh->input_layout_bind();
    CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, mesh->get_index_count(), GL_UNSIGNED_INT, nullptr));
    mesh->input_layout_unbind();
}

void GLRenderer::draw(Model &model) {
    for (auto& mesh : model.get_meshes()) {
        draw_mesh(mesh);
    }
}

void GLRenderer::clear() {
    CHECK_GL_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void GLRenderer::clear_color(glm::vec4 color) {
    CHECK_GL_ERROR(glClearColor(color.x, color.y, color.z, color.a));
}
