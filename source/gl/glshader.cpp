#include "gl.hpp"
#include "draw.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

static GLShader glshader;

std::string readFile(const std::string &path) {
    std::stringstream result;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(path);
        result << file.rdbuf();
        file.close();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << path << std::endl;
    }
    return result.str();
}

unsigned int compileShader(unsigned int type, const char *source) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::string errorType = type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
        std::cout << "ERROR::SHADER::" << errorType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }
    return shader;
}

unsigned int createProgram() {
    glshader.programId = glCreateProgram();
    glAttachShader(glshader.programId, glshader.vertexShader);
    glAttachShader(glshader.programId, glshader.fragmentShader);
    glLinkProgram(glshader.programId);

    int success;
    char infoLog[512];
    glGetProgramiv(glshader.programId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(glshader.programId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    glDeleteShader(glshader.fragmentShader);
    glDeleteShader(glshader.vertexShader);
    return 1;
}

void Shader::init(std::string vertexSource, std::string fragmentSource) {
    glshader.vertexShader = compileShader(GL_VERTEX_SHADER, readFile(vertexSource).c_str());
    glshader.fragmentShader = compileShader(GL_FRAGMENT_SHADER, readFile(fragmentSource).c_str());
    createProgram();
}

void Shader::use() {
    glUseProgram(glshader.programId);
}

void Shader::setWireframe() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(glshader.programId, name.c_str()), value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(glshader.programId, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(glshader.programId, name.c_str()), value);
}
