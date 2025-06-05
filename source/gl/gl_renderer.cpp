#include "gl/gl_renderer.hpp"
#include "gl/gl.hpp"

#include <unordered_set>

static std::unordered_set<std::string> logged_messages;

static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    if (logged_messages.insert(message).second) {
        std::cout << "[GL DEBUG] "
                  << "Type: " << type
                  << ", Severity: " << severity
                  << ", Message: " << message << std::endl;
    }
}

void GLRenderer::init() {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, nullptr);

    // CHECK_GL_ERROR(glEnable(GL_DEPTH_TEST));
    // CHECK_GL_ERROR(glDepthFunc(GL_LEQUAL));
    CHECK_GL_ERROR(glEnable(GL_BLEND));
    CHECK_GL_ERROR(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    // CHECK_GL_ERROR(glEnable(GL_SCISSOR_TEST));

    clear_color();
    clear();

    asset_manager = get_asset_manager();
}

//TODO: replace with draw_sprite
void GLRenderer::draw_mesh(const Mesh& mesh) {
    // asset_manager->get_texture(mesh.get_texture())->bind();
    // mesh.input_layout_bind();
    // mesh.bind();
    // CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, mesh.get_index_count(), GL_UNSIGNED_INT, nullptr));
    // mesh.input_layout_unbind();
}

void GLRenderer::draw(const Model& model) {
    for (auto& mesh : model.get_meshes()) {
        draw_mesh(*mesh);
    }
}

void GLRenderer::set_shader(Shader& shader) {
    shader.bind();
    shader.set_image("uTexture", 0);
    // shader.set_wireframe();
}

void GLRenderer::set_wireframe() {
    CHECK_GL_ERROR(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
}

void GLRenderer::clear() {
    CHECK_GL_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void GLRenderer::clear_color(glm::vec4 color) {
    CHECK_GL_ERROR(glClearColor(color.x, color.y, color.z, color.a));
}
