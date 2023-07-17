#pragma once
#define GLFW_INCLUDE_NONE
#include <glm/glm.hpp>
#include <glfw/glfw3.h>

#include <string>
#include <memory>

class Window {
    struct GLFWwindowDeleter {
        void operator()(void *window) {
            glfwDestroyWindow((GLFWwindow*)window);
        }
    };
public:
    Window(const std::string &title, glm::vec2 size = {1280, 720}, glm::vec2 position = {-1, -1});
    
    glm::vec2 size() const;
    bool running();
    void *instance() const;
    
    void pollEvents();
    void swap();
    void destroy();
private:
    std::unique_ptr<void, GLFWwindowDeleter> window;
};
