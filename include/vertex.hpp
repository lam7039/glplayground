#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec4 color {1.0f};
    glm::vec2 texCoords;
    float textureId {0.0f};
};

class VertexArray {
    unsigned int indexCount {0};
public:
    void init(std::vector<Vertex> &vertices);
    void bind(std::vector<Vertex> &vertices);
    void draw();
    void clear();
};
