#pragma once

#include <string>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texCoords;
    float textureId;
};

struct Window {
    bool running {false};
    glm::vec2 position, size;
    void **window {nullptr};
    void *context {nullptr};
};

class Context {
public:
    void init(glm::vec2 position, glm::vec2 size, void **glFuncName);
    void clearColor(glm::vec4 color = {0.2f, 0.2f, 0.2f, 1.0f});
    void clear();
};

class VertexArray {
public:
    void init();
    void bind();
    void draw();
};
