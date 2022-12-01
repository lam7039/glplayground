#pragma once

#include <string>
#include "vector2.hpp"

class Shader {
public:
    virtual void init(const std::string &vertexSource = "../shaders/vertex.glsl", const std::string &fragmentSource = "../shaders/fragment.glsl") = 0;
    virtual void use() = 0;
    virtual void setWireframe() = 0;
    virtual void setBool(const std::string &name, bool value) const = 0;
    virtual void setInt(const std::string &name, int value) const = 0;
    virtual void setFloat(const std::string &name, float value) const = 0;
};

class Texture {
public:
    virtual void init(vector2i size, const void *data, bool hasAlpha) = 0;
    virtual void bind() = 0;
    virtual void free() = 0;
};

class VertexArrays {
public:
    virtual void init() = 0;
    virtual void draw() = 0;
};
