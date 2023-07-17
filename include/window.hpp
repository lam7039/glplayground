#pragma once
#define GLFW_INCLUDE_NONE
#include <glm/glm.hpp>
#include <glfw/glfw3.h>

#include <string>
#include <memory>

//TODO: use forward declaration and move <glfw/glfw.h> to source file
// typedef struct GLFWwindow GLFWwindow;

class Window {
    struct GLFWwindowDeleter {
        void operator()(GLFWwindow *window) {
            glfwDestroyWindow(window);
        }
    };
public:
    Window(const std::string &title, glm::vec2 size = {1280, 720}, glm::vec2 position = {-1, -1});
    
    glm::vec2 size() const;
    bool running();
    GLFWwindow *instance() const;
    
    void pollEvents();
    void swap();
    void destroy();
private:
    std::unique_ptr<GLFWwindow, GLFWwindowDeleter> window;
};
