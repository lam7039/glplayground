#pragma once

#include <glm/glm.hpp>

#include <string>
#include <memory>

struct GLFWwindow;

// class IWindow {
// public:
//     virtual glm::vec2 size() const = 0;
//     virtual bool running();
//     virtual GLFWwindow *instance() const = 0;

//     virtual void pollEvents() = 0;
//     virtual void swap() = 0;
//     virtual void close() = 0;
//     virtual void destroy() = 0;
// };

class Window {
    struct GLFWwindowDeleter {
        void operator()(GLFWwindow *window);
    };
public:
    Window(const std::string &title, glm::vec2 size = {1280, 720}, glm::vec2 position = {-1, -1});
    
    glm::vec2 size() const;
    bool running();
    GLFWwindow *instance() const;
    
    void poll_events();
    void swap();
    void close();
    void destroy();
private:
    std::unique_ptr<GLFWwindow, GLFWwindowDeleter> window;
};
