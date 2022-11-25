#pragma once

#define GLEW_STATIC

#include <string>
#include "vector2.hpp"
#include "vector3.hpp"

class GLContext {
public:
    GLContext();
    void init(vector2i position, vector2i size, vector3f color = vector3f(0.2f, 0.2f, 0.2f));
    void clear();
};

class Shader {
    unsigned int programId;
    unsigned int vertexShader, fragmentShader;

    std::string readFile(const std::string &path);
    unsigned int compile(unsigned int type, const char *source);
    unsigned int createProgram();
public:
    Shader(const std::string &vertexSource = "../shaders/vertex.glsl", const std::string &fragmentSource = "../shaders/fragment.glsl");
    void use();
    void setWireframe();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

class VertexArray {
    unsigned int vertexArrayObject, vertexBufferObject, elementBufferObject;
public:
    VertexArray();
    void draw();
};