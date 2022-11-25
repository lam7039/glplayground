#pragma once

#define GLEW_STATIC

#include <string>
#include "vector2.hpp"

class OpenGL {
    unsigned int vertexArrayObject, vertexBufferObject, elementBufferObject;
public:
    OpenGL(vector2i position, vector2i size);
    void init();
    void clear();
    void draw();
};

class Shader {
    unsigned int programId;
    unsigned int vertexShader, fragmentShader;

    std::string readFile(const std::string& path);
    unsigned int compile(unsigned int type, const char *source);
    unsigned int createProgram();
public:
    Shader();
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};
