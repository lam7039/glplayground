#pragma once

#include <string>
#include <iostream>
#include <signal.h>

#define GLFW_INCLUDE_NONE
#include "glfw/glfw3.h"
#include "glad/gl.h"
#include "glm/glm.hpp"

#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char *function, const char *file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

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
