#include "renderer.hpp"
#include "gl.hpp"

void Renderer::init() {
    // CHECK_GL_ERROR(glEnable(GL_DEPTH_TEST));
    // CHECK_GL_ERROR(glDepthFunc(GL_LEQUAL));
    CHECK_GL_ERROR(glEnable(GL_BLEND));
    CHECK_GL_ERROR(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    // CHECK_GL_ERROR(glEnable(GL_SCISSOR_TEST));

    clearColor();
    clear();

    shader = get_asset<Shader>("main");
    shader->bind();
    shader->setImage("ourTexture", 0);
}

void Renderer::drawMesh(const std::unique_ptr<Mesh> &mesh) {
    get_asset<Texture>(mesh->getTexture())->bind();
    mesh->inputLayoutBind();
    CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_INT, nullptr));
    mesh->inputLayoutUnbind();
}

void Renderer::draw(Model &model) {
    for (auto &mesh : model.getMeshes()) {
        drawMesh(mesh);
    }
}

void Renderer::clear() {
    CHECK_GL_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::clearColor(glm::vec4 color) {
    CHECK_GL_ERROR(glClearColor(color.x, color.y, color.z, color.a));
}
