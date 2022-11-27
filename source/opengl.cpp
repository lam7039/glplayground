#include "opengl.hpp"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>

void GLContext::init(vector2i position, vector2i size, vector3f color) {
    glewExperimental = true;
    if (GLenum error = glewInit(); error != GLEW_OK) {
        std::cout << "glewInit failed: " << glewGetErrorString(error) << std::endl;
        return;
    }

    std::cout << "Vendor graphic card:  " << glGetString(GL_VENDOR) << std::endl
              << "Renderer:             " << glGetString(GL_RENDERER) << std::endl
              << "GL version:           " << glGetString(GL_VERSION) << std::endl
              << "GLSL version:         " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LEQUAL);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_SCISSOR_TEST);

    glViewport(position.x, position.y, size.x, size.y);
    glClearColor(color.x, color.y, color.z, 1.0f);
}

void GLContext::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

Shader::Shader(const std::string &vertexSource, const std::string &fragmentSource) {
    vertexShader = compile(GL_VERTEX_SHADER, readFile(vertexSource).c_str());
    fragmentShader = compile(GL_FRAGMENT_SHADER, readFile(fragmentSource).c_str());
    createProgram();
}

std::string Shader::readFile(const std::string &path) {
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

unsigned int Shader::compile(unsigned int type, const char *source) {
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

unsigned int Shader::createProgram() {
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

void Shader::use() {
    glUseProgram(programId);
}

void Shader::setWireframe() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}

Object::Object() {
    //xyz rgb
    //TODO: add st (which is the same as uv with 2D textures)
    float vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,     // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,    // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f     // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    float texCoords[] = {
        0.0f, 0.0f,  // lower-left corner  
        1.0f, 0.0f,  // lower-right corner
        0.0f, 1.0f,  // top-left corner
        1.0f, 1.0f   // top-right corner
    };

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Object::draw() {
    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

// Texture::Texture(int width, int height, const void *pixels, unsigned int bytesPerPixel) {
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

//     float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
//     glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


//     glGenTextures(1, &id);
//     glBindTexture(GL_TEXTURE_2D, id);
//     int mode = bytesPerPixel == 4 ? GL_RGBA : GL_RGB;
//     glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, pixels);
// }