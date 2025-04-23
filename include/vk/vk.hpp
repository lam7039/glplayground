#pragma once

#include <iostream>
#include <signal.h>

#include "vulkan/vulkan.h"

#if NDEBUG
    #define CHECK_VK_ERROR(VK_CALL) VK_CALL;
#else
    #ifdef _WIN32
        #define ASSERT(x) if (!(x)) __debugbreak();
    #else
        #define ASSERT(x) if (!(x)) raise(SIGTRAP);
    #endif
    #define CHECK_VK_ERROR(VK_CALL) \
        VkResult error = VK_CALL;\
        ASSERT(VKLogCall(error, #VK_CALL, __FILE__, __LINE__))
#endif

static bool VKLogCall(VkResult error, const char *function, const char *file, int line) {
    if (VK_SUCCESS != error) {
        std::printf("[Vulkan Error] (%d): %s %s %d\n", error, function, file, line);
        return false;
    }
    return true;
}

struct VKBuffer {
    unsigned int id {0};
};

struct VKShader {
    unsigned int program_id {0};
    unsigned int vertex_shader {0};
    unsigned int fragment_shader {0};
};

// struct VKVertexArray {
//     unsigned int vertex_array_object {0};
//     unsigned int vertex_buffer_object {0};
//     unsigned int element_buffer_object {0};
// };
