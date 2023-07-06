#pragma once

#include "vertex.hpp"

class Quad {
public:
    Quad();
    ~Quad();
    //TODO: don't set textureId in Quad
    Quad(glm::vec3 &position, glm::vec3 &size, float textureId = 0);

    void draw(glm::vec3 &position, glm::vec3 &size, float textureId);
    void destroy();
private:
    //TODO: move vertices to VertexArray
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    VertexArray vertexArray;

    void setTexCoords(float x, float y, float width, float height, float textureId);
    std::vector<unsigned int> generateIndices();
};
