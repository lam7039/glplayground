#pragma once

#include <glm/glm.hpp>

#include <string>
#include <memory>

struct GLFWwindow;

class Window {
    struct GLFWwindowDeleter {
        void operator()(GLFWwindow *window);
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
