#pragma once

#include <string>
#include <glm/glm.hpp>

class Window {
public:
    Window(const std::string &title, glm::vec2 size = {1280, 720}, glm::vec2 position = {-1, -1});
    
    glm::vec2 size() const;
    bool running();
    void *instance() const;
    
    void pollEvents();
    void swap();
    void destroy();
private:
    void *window {nullptr};
};
