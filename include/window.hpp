#pragma once

#include <string>
#include <glm/glm.hpp>

class Window {
    void *window {nullptr};
public:
    Window(const std::string &title, glm::vec2 size = {1280, 720}, glm::vec2 position = {-1, -1});
    
    glm::vec2 size() const;
    bool running();
    void pollEvents();
    void clear();
    void clearColor(glm::vec4 color = {0.2f, 0.2f, 0.2f, 1.0f});
    void swap();
    
    void destroy();
    void quit();
};
