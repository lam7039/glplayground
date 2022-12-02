#pragma once

#include <string>
#include "vector2.hpp"
#include "vector3.hpp"

class Context {
public:
    vector2i position;
    vector2i size;
    vector3f color;

    void init(vector2i position, vector2i size, void **proc);
    void clearColor(vector3f color = vector3f(0.2f, 0.2f, 0.2f));
    void clear();
};

class Shader {
public:
    void init(std::string vertexSource = "../shaders/vertex.glsl", std::string fragmentSource = "../shaders/fragment.glsl");
    void use();
    void setWireframe();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

class Texture {
public:
    void init(vector2i size, const void *data, bool hasAlpha);
    void bind();
    void free();
};

class VertexArray {
public:
    void init();
    void draw();
};
