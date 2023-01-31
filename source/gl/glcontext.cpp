#include "gl.hpp"
#include "draw.hpp"
// #include "game.hpp" or maybe put context class in windows.hpp?
#include <iostream>

static GLContext context;

void Context::init(glm::vec2 position, glm::vec2 size, void **glFuncName) {
    context = {position, size, {0.2f, 0.2f, 0.2f, 1.0f}};

    if (!gladLoadGL((GLADloadfunc)glFuncName)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    std::cout << "Vendor graphic card:  " << glGetString(GL_VENDOR) << std::endl
              << "Renderer:             " << glGetString(GL_RENDERER) << std::endl
              << "GL version:           " << glGetString(GL_VERSION) << std::endl
              << "GLSL version:         " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_SCISSOR_TEST);

    glViewport(position.x, position.y, size.x, size.y);
    this->clearColor();
}

void Context::clearColor(glm::vec4 color) {
    glClearColor(color.x, color.y, color.z, color.a);
}

void Context::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}
