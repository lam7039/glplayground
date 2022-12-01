#pragma once

#include "draw.hpp"

class Object {
    Shader shader;
    Texture texture;
    VertexArray vertexArrays;
public:
    void init(vector2i size, const void *data, bool hasAlpha);
    void draw();
    void free();
};
