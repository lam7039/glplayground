#pragma once

#include "mesh.hpp"
#include <memory>

class Rectangle {
public:
    Rectangle();
    Rectangle(glm::vec3 &position, glm::vec3 &size, std::string texture);
    // ~Rectangle();

    void transform(glm::vec3 &position, glm::vec3 &size);
    void destroy();

    std::unique_ptr<Mesh> &getMesh();
private:
    unsigned int vertexBufferIndex {0};
    std::vector<Vertex> vertices;
    std::unique_ptr<Mesh> mesh;

    void generateVertices(glm::vec3 position, glm::vec3 size);
    std::vector<unsigned int> generateIndices();
};
