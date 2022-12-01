#pragma once

#include "vector2.hpp"
#include "draw.hpp"

class Object {
    Shader *shader;
    Texture *texture;
    VertexArrays *vertexArrays;
public:
    Object();
    void init(vector2i size, const void *data, bool hasAlpha);
    void draw();
    void free();
};