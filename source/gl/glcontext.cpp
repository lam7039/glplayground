#include "gl.hpp"
#include <SDL2/SDL.h>
#include <iostream>

void ContextGL::init(vector2i position, vector2i size, vector3f color) {
    if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
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
    glClearColor(color.x, color.y, color.z, 1.0f);
}

void ContextGL::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}
