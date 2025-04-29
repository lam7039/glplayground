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

static bool VKLogCall(VkResult error, const char* function, const char* file, int line) {
    if (VK_SUCCESS != error) {
        std::printf("[Vulkan Error] (%d): %s %s %d\n", error, function, file, line);
        return false;
    }
    return true;
}
