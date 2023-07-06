#include "mesh.hpp"

Mesh::Mesh(const std::vector<float> &vertices, const std::vector<unsigned int> &indices) : vertexData(vertices), indexData(indices) {}

const float *Mesh::getVertexDataPtr() const {
    return vertexData.data();
}

unsigned int Mesh::getVertexDataSize() const {
    return static_cast<unsigned int>(vertexData.size() * sizeof(float));
}

unsigned int Mesh::getIndexCount() const {
    return static_cast<unsigned int>(indexData.size());
}

