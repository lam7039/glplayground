#pragma once

#include "draw.hpp"

class Object {
    std::string basePath;
    Shader shader;
    Texture texture;
    VertexArray vertexArrays;
public:
    Object(std::string basePath);
    void init(vector2i size, const void *data, bool hasAlpha);
    void draw();
    void free();
};
