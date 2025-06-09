#include "gl/gl.hpp"
#include "shader.hpp"

#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

enum ShaderType {
    Vertex = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER
};

static std::string read_file(std::string_view path) {
    std::stringstream result;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(std::string(path));
        result << file.rdbuf();
        file.close();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << path << std::endl;
    }
    return result.str();
}

static unsigned int compile_shader(ShaderType type, const char* source) {
    CHECK_GL_ERROR(unsigned int shader = glCreateShader(type));
    CHECK_GL_ERROR(glShaderSource(shader, 1, &source, nullptr));
    CHECK_GL_ERROR(glCompileShader(shader));

    int success;
    CHECK_GL_ERROR(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (!success) {
        int length;
        CHECK_GL_ERROR(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));

        char message[length];
        CHECK_GL_ERROR(glGetShaderInfoLog(shader, length, &length, message));

        std::string error_type = type == ShaderType::Vertex ? "VERTEX" : "FRAGMENT";
        std::cout << "ERROR::SHADER::" << error_type << "::COMPILATION_FAILED\n" << message << std::endl;

        return 0;
    }

    return shader;
}

static unsigned int create_program(unsigned int vertex_shader, unsigned int fragment_shader) {
    CHECK_GL_ERROR(unsigned int program_id = glCreateProgram());
    CHECK_GL_ERROR(glAttachShader(program_id, vertex_shader));
    CHECK_GL_ERROR(glAttachShader(program_id, fragment_shader));
    CHECK_GL_ERROR(glLinkProgram(program_id));

    int success;
    CHECK_GL_ERROR(glGetProgramiv(program_id, GL_LINK_STATUS, &success));
    if (!success) {
        int length;
        CHECK_GL_ERROR(glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length))

        char message[length];
        CHECK_GL_ERROR(glGetProgramInfoLog(program_id, length, &length, message));
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << message << std::endl;

        return 0;
    }

    CHECK_GL_ERROR(glDeleteShader(fragment_shader));
    CHECK_GL_ERROR(glDeleteShader(vertex_shader));
    
    return program_id;
}

Shader::Shader(std::string_view vertex_source, std::string_view fragment_source) : vertex_source(std::string(vertex_source)), fragment_source(std::string(fragment_source)) {}

void Shader::load() {
    auto vertex_shader = compile_shader(ShaderType::Vertex, read_file(vertex_source).c_str());
    auto fragment_shader = compile_shader(ShaderType::Fragment, read_file(fragment_source).c_str());
    program_id = create_program(vertex_shader, fragment_shader);

    // std::unordered_map<ShaderType, std::string> shader_sources;

    // create_program();
    // for (auto& [type, source] : shader_sources) {
    //     compile_shader(type, source);
    // }

    // link_program();
    // for (auto& [type, source] : shader_sources) {
    //     CHECK_GL_ERROR(glDeleteShader(source));
    // }

    // destroy();
}

void Shader::bind() {
    CHECK_GL_ERROR(glUseProgram(program_id));
}

void Shader::destroy() {
    CHECK_GL_ERROR(glDeleteProgram(program_id));
}

//TODO: separate set_uniforms from shaders somehow, perhaps a separate header with static definitions and defining the static definitions here
void Shader::set_bool(std::string_view name, bool value) {
    CHECK_GL_ERROR(glUniform1i(get_location(name), value));
}

void Shader::set_int(std::string_view name, int value) {
    CHECK_GL_ERROR(glUniform1i(get_location(name), value));
}

void Shader::set_float(std::string_view name, float value) {
    CHECK_GL_ERROR(glUniform1f(get_location(name), value));
}

void Shader::set_image(std::string_view name, int* samplers) {
    int count = sizeof(samplers) / sizeof(int);
    CHECK_GL_ERROR(glUniform1iv(get_location(name), count, samplers));
}

void Shader::set_image(std::string_view name, int sampler) {
    set_int(name, sampler);
}

void Shader::set_matrix(std::string_view name, const glm::mat4& matrix) {
    CHECK_GL_ERROR(glUniformMatrix4fv(get_location(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}

int Shader::get_location(std::string_view name) {
    if (uniform_location_cache.find(std::string(name)) != uniform_location_cache.end()) {
        return uniform_location_cache[std::string(name)];
    }
    
    CHECK_GL_ERROR(int location = glGetUniformLocation(program_id, name.data()));
    if (location == -1) {
        std::cout << "WARNING: uniform '" << name << "' doesn't exist" << std::endl;
    }

    uniform_location_cache[std::string(name)] = location;
    return location;
}
