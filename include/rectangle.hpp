#pragma once

#include "vertex.hpp"

class Rectangle {
public:
    Rectangle();
    ~Rectangle();
    Rectangle(float x, float y, float width, float height, float textureId = 0);

    void draw();
private:
    //TODO: move vertices to VertexArray
    std::vector<Vertex> vertices;
    VertexArray vertexArray;

    void setTexCoords(float x, float y, float width, float height, float textureId);
};
