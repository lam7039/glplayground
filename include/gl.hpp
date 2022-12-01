#pragma once

#include <string>
#include <glad/gl.h>
// #include "thirdparty/include/glad/glad.h"

#include "draw.hpp"
#include "vector3.hpp"

class ContextGL {
public:
    void init(vector2i position, vector2i size, vector3f color = vector3f(0.2f, 0.2f, 0.2f));
    void clear();
};

class ShaderGL : public Shader {
    unsigned int programId;
    unsigned int vertexShader, fragmentShader;

    std::string readFile(const std::string &path);
    unsigned int compile(unsigned int type, const char *source);
    unsigned int createProgram();
public:
    void init(const std::string &vertexSource = "../shaders/vertex.glsl", const std::string &fragmentSource = "../shaders/fragment.glsl") override;
    void use() override;
    void setWireframe() override;
    void setBool(const std::string &name, bool value) const override;
    void setInt(const std::string &name, int value) const override;
    void setFloat(const std::string &name, float value) const override;
};

class TextureGL : public Texture {
    unsigned int id;
public:
    void init(vector2i size, const void *data, bool hasAlpha) override;
    void bind() override;
    void free() override;
};

class VertexArraysGL : public VertexArrays {
    unsigned int vertexArrayObject, vertexBufferObject, elementBufferObject;
public:
    void init();
    void draw();
};
