#pragma once

#include <iostream>

#include "glad/gl.h"

#if NDEBUG
    #define CHECK_GL_ERROR(GL_CALL) GL_CALL;
#else
    #ifdef _WIN32
        #include <intrin.h>
        #define ASSERT(x) if (!(x)) __debugbreak();
    #else
        #include <csignal>
        #define ASSERT(x) if (!(x)) raise(SIGTRAP);
    #endif
    #define CHECK_GL_ERROR(GL_CALL) \
        GL_CALL;\
        ASSERT(GLLogCall(#GL_CALL, __FILE__, __LINE__))
#endif

static bool GLLogCall(const char* function, const char* file, int line) {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::printf("[OpenGL Error] (%d): %s %s %d\n", error, function, file, line);
        return false;
    }
    return true;
}
