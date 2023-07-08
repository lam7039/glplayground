#pragma once

#include "mesh.hpp"

class Quad {
public:
    Quad();
    ~Quad();
    //TODO: don't set textureId in Quad
    Quad(glm::vec3 &position, glm::vec3 &size, float textureId = 0);

    void transform(glm::vec3 &position, glm::vec3 &size, float textureId);
    void destroy();

    Mesh &getMesh();
private:
    //TODO: move vertices to Mesh
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Mesh *mesh;

    void setTexCoords(float x, float y, float width, float height, float textureId);
    std::vector<unsigned int> generateIndices();
};
