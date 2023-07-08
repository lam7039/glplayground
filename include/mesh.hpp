#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 position {0.0f};
    glm::vec4 color {1.0f};
    glm::vec2 texCoords;
    float textureId {0.0f};
};

class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    void bind(std::vector<Vertex> &vertices);
    void inputLayoutBind();
    void inputLayoutUnBind();
    void destroy();
    
    unsigned int getIndexCount() const;
private:
    std::vector<Vertex> vertexData;
    std::vector<unsigned int> indexData;

    unsigned int inputLayoutObject;
    unsigned int vertexBufferObject;
    unsigned int indexBufferObject;
    
    unsigned int getVertexDataSize() const;
};
