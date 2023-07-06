#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 position {0.0f};
    glm::vec4 color {1.0f};
    glm::vec2 texCoords;
    float textureId {0.0f};
};

class VertexArray {
public:
    void init(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
    void bind(std::vector<Vertex> &vertices);
    void draw();
    void clear();
private:
    unsigned int vertexDataSize {0};
    unsigned int indexCount {0};
    
    unsigned int vertexArrayObject {0};
    unsigned int vertexBufferObject {0};
    unsigned int elementBufferObject {0};
};
