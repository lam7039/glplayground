#pragma once

#include "assets.hpp"

class Object {
    std::string basePath;
    Shader shader;
    Texture texture;
    VertexArray vertexArrays;
public:
    Object(std::string basePath);
    void init(Asset *asset);
    void draw(int index);
    void destroy();
};
