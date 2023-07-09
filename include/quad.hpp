#pragma once

#include "mesh.hpp"

class Quad {
public:
    Quad();
    Quad(glm::vec3 &position, glm::vec3 &size, float textureId = 0);
    // ~Quad();

    void transform(glm::vec3 &position, glm::vec3 &size);
    void destroy();

    Mesh *getMesh();
private:
    unsigned int vertexBufferIndex {0};
    std::vector<Vertex> vertices;
    Mesh *mesh;

    void generateVertices(glm::vec3 position, glm::vec3 size, float textureId = 0);
    std::vector<unsigned int> generateIndices();
};
