#include "gl.hpp"
#include "assets.hpp"
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
    GLCall(glShaderSource(shader, 1, &source, NULL));
    GLCall(glCompileShader(shader));

    int success;
    char infoLog[512];
    GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (!success) {
        GLCall(glGetShaderInfoLog(shader, 512, NULL, infoLog));
        std::string errorType = type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
        std::cout << "ERROR::SHADER::" << errorType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }
    return shader;
}

unsigned int createProgram() {
    GLCall(glshader.programId = glCreateProgram());
    GLCall(glAttachShader(glshader.programId, glshader.vertexShader));
    GLCall(glAttachShader(glshader.programId, glshader.fragmentShader));
    GLCall(glLinkProgram(glshader.programId));

    int success;
    char infoLog[512];
    GLCall(glGetProgramiv(glshader.programId, GL_LINK_STATUS, &success));
    if (!success) {
        GLCall(glGetProgramInfoLog(glshader.programId, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    GLCall(glDeleteShader(glshader.fragmentShader));
    GLCall(glDeleteShader(glshader.vertexShader));
    return 1;
}

Shader::Shader(const std::string &name, const std::string &vertexSource, const std::string &fragmentSource) : Asset(name, SHADER) {
    glshader.vertexShader = compileShader(GL_VERTEX_SHADER, readFile(vertexSource).c_str());
    glshader.fragmentShader = compileShader(GL_FRAGMENT_SHADER, readFile(fragmentSource).c_str());
    createProgram();
}

void Shader::bind() {
    GLCall(glUseProgram(glshader.programId));
}

void Shader::setWireframe() {
    GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
}

int Shader::getLocation(const std::string &name) const {
    GLCall(int location = glGetUniformLocation(glshader.programId, name.c_str()));
    return location;
}

void Shader::setBool(const std::string &name, bool value) {
    GLCall(glUniform1i(getLocation(name), value));
}

void Shader::setInt(const std::string &name, int value) {
    GLCall(glUniform1i(getLocation(name), value));
}

void Shader::setFloat(const std::string &name, float value) {
    GLCall(glUniform1f(getLocation(name), value));
}

void Shader::setImage(const std::string &name, int *samplers) {
    int count = sizeof(samplers) / sizeof(int);
    GLCall(glUniform1iv(getLocation(name), count, samplers));
}

void Shader::setMatrix(const std::string &name, const glm::mat4 &matrix) {
    GLCall(glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, &matrix[0][0]));
}
