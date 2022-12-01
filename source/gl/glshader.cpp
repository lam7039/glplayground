#include "gl.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

void ShaderGL::init(const std::string &vertexSource, const std::string &fragmentSource) {
    vertexShader = compile(GL_VERTEX_SHADER, readFile(vertexSource).c_str());
    fragmentShader = compile(GL_FRAGMENT_SHADER, readFile(fragmentSource).c_str());
    createProgram();
}

std::string ShaderGL::readFile(const std::string &path) {
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

unsigned int ShaderGL::compile(unsigned int type, const char *source) {
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

unsigned int ShaderGL::createProgram() {
    programId = glCreateProgram();
    glAttachShader(programId, vertexShader);
    glAttachShader(programId, fragmentShader);
    glLinkProgram(programId);

    int success;
    char infoLog[512];
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    return 1;
}

void ShaderGL::use() {
    glUseProgram(programId);
}

void ShaderGL::setWireframe() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void ShaderGL::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

void ShaderGL::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

void ShaderGL::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}