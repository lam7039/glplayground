#include "gl.hpp"
#include "assets.hpp"
#include <fstream>
#include <sstream>

static std::string readFile(const std::string &path) {
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

unsigned int Shader::compileShader(unsigned int type, const char *source) {
    unsigned int shader = glCreateShader(type);
    CHECK_GL_ERROR(glShaderSource(shader, 1, &source, NULL));
    CHECK_GL_ERROR(glCompileShader(shader));

    int success;
    char infoLog[512];
    CHECK_GL_ERROR(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (!success) {
        CHECK_GL_ERROR(glGetShaderInfoLog(shader, 512, NULL, infoLog));
        std::string errorType = type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
        std::cout << "ERROR::SHADER::" << errorType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }
    return shader;
}

unsigned int Shader::createProgram() {
    CHECK_GL_ERROR(programId = glCreateProgram());
    CHECK_GL_ERROR(glAttachShader(programId, vertexShader));
    CHECK_GL_ERROR(glAttachShader(programId, fragmentShader));
    CHECK_GL_ERROR(glLinkProgram(programId));

    int success;
    char infoLog[512];
    CHECK_GL_ERROR(glGetProgramiv(programId, GL_LINK_STATUS, &success));
    if (!success) {
        CHECK_GL_ERROR(glGetProgramInfoLog(programId, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    CHECK_GL_ERROR(glDeleteShader(fragmentShader));
    CHECK_GL_ERROR(glDeleteShader(vertexShader));
    return 1;
}

Shader::Shader(const std::string &name, const std::string &vertexSource, const std::string &fragmentSource) : Asset(name, SHADER) {
    vertexShader = compileShader(GL_VERTEX_SHADER, readFile(vertexSource).c_str());
    fragmentShader = compileShader(GL_FRAGMENT_SHADER, readFile(fragmentSource).c_str());
    createProgram();
}

void Shader::bind() {
    CHECK_GL_ERROR(glUseProgram(programId));
}

void Shader::setWireframe() {
    CHECK_GL_ERROR(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
}

void Shader::setBool(const std::string &name, bool value) {
    CHECK_GL_ERROR(glUniform1i(getLocation(name), value));
}

void Shader::setInt(const std::string &name, int value) {
    CHECK_GL_ERROR(glUniform1i(getLocation(name), value));
}

void Shader::setFloat(const std::string &name, float value) {
    CHECK_GL_ERROR(glUniform1f(getLocation(name), value));
}

void Shader::setImage(const std::string &name, int *samplers) {
    int count = sizeof(samplers) / sizeof(int);
    CHECK_GL_ERROR(glUniform1iv(getLocation(name), count, samplers));
}

void Shader::setMatrix(const std::string &name, const glm::mat4 &matrix) {
    CHECK_GL_ERROR(glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::getLocation(const std::string &name) {
    if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
        return uniformLocationCache[name];
    }
    
    CHECK_GL_ERROR(int location = glGetUniformLocation(programId, name.c_str()));
    if (location == -1) {
        std::cout << "WARNING: uniform '" << name << "' doesn't exist" << std::endl;
    }

    uniformLocationCache[name] = location;
    return location;
}
