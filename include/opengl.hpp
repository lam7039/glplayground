#pragma once

#define GLEW_STATIC

#include <string>
#include "vector2.hpp"

class OpenGL {
    unsigned int vertexArrayObject, vertexBufferObject, elementBufferObject;
public:
    OpenGL(vector2i pos, vector2i size);
    void init();
    void draw();
    void clear();
};

class Shader {
    unsigned int programId;
    unsigned int vertexShader, fragmentShader;

    const char* readFile(const std::string& path);
    unsigned int compile(unsigned int type, const char *source);
    unsigned int createProgram();
public:
    Shader();
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};