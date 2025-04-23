#pragma once

#include <iostream>
#include <signal.h>

#include "glad/gl.h"

#if NDEBUG
    #define CHECK_GL_ERROR(GL_CALL) GL_CALL;
#else
    #ifdef _WIN32
        #define ASSERT(x) if (!(x)) __debugbreak();
    #else
        #define ASSERT(x) if (!(x)) raise(SIGTRAP);
    #endif
    #define CHECK_GL_ERROR(GL_CALL) \
        GL_CALL;\
        ASSERT(GLLogCall(#GL_CALL, __FILE__, __LINE__))
#endif

static bool GLLogCall(const char *function, const char *file, int line) {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::printf("[OpenGL Error] (%d): %s %s %d\n", error, function, file, line);
        return false;
    }
    return true;
}

struct GLBuffer {
    unsigned int id {0};
};

struct GLShader {
    unsigned int program_id {0};
    unsigned int vertex_shader {0};
    unsigned int fragment_shader {0};
};

// struct GLVertexArray {
//     unsigned int vertex_array_object {0};
//     unsigned int vertex_buffer_object {0};
//     unsigned int element_buffer_object {0};
// };
