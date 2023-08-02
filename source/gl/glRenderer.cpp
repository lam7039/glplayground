#include "renderer.hpp"
#include "gl.hpp"
#include "assets.hpp"

Renderer::Renderer() {
    // CHECK_GL_ERROR(glEnable(GL_DEPTH_TEST));
    // CHECK_GL_ERROR(glDepthFunc(GL_LEQUAL));
    CHECK_GL_ERROR(glEnable(GL_BLEND));
    CHECK_GL_ERROR(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    // CHECK_GL_ERROR(glEnable(GL_SCISSOR_TEST));

    clearColor();
    clear();
}

void Renderer::drawMesh(const std::unique_ptr<Mesh> &mesh) {
    getAssetLoader()->find<Texture>(mesh->getTexture())->bind();
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
