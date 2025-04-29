#include "gl/gl.hpp"
#include "shader.hpp"
#include <fstream>
#include <sstream>

static std::string read_file(const std::string& path) {
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

unsigned int Shader::compile_shader(unsigned int type, const char* source) {
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

unsigned int Shader::create_program() {
    CHECK_GL_ERROR(id = glCreateProgram());
    CHECK_GL_ERROR(glAttachShader(id, vertex_shader));
    CHECK_GL_ERROR(glAttachShader(id, fragment_shader));
    CHECK_GL_ERROR(glLinkProgram(id));

    int success;
    char infoLog[512];
    CHECK_GL_ERROR(glGetProgramiv(id, GL_LINK_STATUS, &success));
    if (!success) {
        CHECK_GL_ERROR(glGetProgramInfoLog(id, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    CHECK_GL_ERROR(glDeleteShader(fragment_shader));
    CHECK_GL_ERROR(glDeleteShader(vertex_shader));
    return 1;
}

Shader::Shader(const std::string& vertex_source, const std::string& fragment_source) : vertex_source(vertex_source), fragment_source(fragment_source) {
    type = AssetType::SHADER;
}

void Shader::init() {
    vertex_shader = compile_shader(GL_VERTEX_SHADER, read_file(vertex_source).c_str());
    fragment_shader = compile_shader(GL_FRAGMENT_SHADER, read_file(fragment_source).c_str());
    create_program();
}

void Shader::bind() {
    CHECK_GL_ERROR(glUseProgram(id));
}

void Shader::set_wireframe() {
    CHECK_GL_ERROR(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
}

void Shader::set_bool(const std::string& name, bool value) {
    CHECK_GL_ERROR(glUniform1i(get_location(name), value));
}

void Shader::set_int(const std::string& name, int value) {
    CHECK_GL_ERROR(glUniform1i(get_location(name), value));
}

void Shader::set_float(const std::string& name, float value) {
    CHECK_GL_ERROR(glUniform1f(get_location(name), value));
}

void Shader::set_image(const std::string& name, int* samplers) {
    int count = sizeof(samplers) / sizeof(int);
    CHECK_GL_ERROR(glUniform1iv(get_location(name), count, samplers));
}

void Shader::set_image(const std::string& name, int sampler) {
    set_int(name, sampler);
}

void Shader::set_matrix(const std::string& name, const glm::mat4& matrix) {
    CHECK_GL_ERROR(glUniformMatrix4fv(get_location(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::get_location(const std::string& name) {
    if (uniform_location_cache.find(name) != uniform_location_cache.end()) {
        return uniform_location_cache[name];
    }
    
    CHECK_GL_ERROR(int location = glGetUniformLocation(id, name.c_str()));
    if (location == -1) {
        std::cout << "WARNING: uniform '" << name << "' doesn't exist" << std::endl;
    }

    uniform_location_cache[name] = location;
    return location;
}

void Shader::destroy() {
    glDeleteProgram(id);
}
