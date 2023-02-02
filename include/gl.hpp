#pragma once

// #include <assert.h>
// assert(glGetError() == GL_NO_ERROR);

#include <string>

// #define GLFW_INCLUDE_NONE
#include "glad/gl.h"
#include "glm/glm.hpp"
#include "glfw/glfw3.h"

struct GLContext {
    glm::vec2 position;
    glm::vec2 size;
    glm::vec4 color;
};

struct GLWindow {
    std::string name;
    glm::vec2 position {-1, -1};
    glm::vec2 size {800, 500};
    GLFWwindow *window {nullptr};
};

struct GLShader {
    unsigned int programId {0};
    unsigned int vertexShader {0};
    unsigned int fragmentShader {0};
};

// struct GLTexture {
//     glm::vec2 size;
//     unsigned int id {0};
// };

struct GLVertexArray {
    unsigned int vertexArrayObject {0};
    unsigned int vertexBufferObject {0};
    unsigned int elementBufferObject {0};
};
