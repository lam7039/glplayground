#include "opengl.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <GL/glew.h>

OpenGL::OpenGL(vector2i pos, vector2i size) {
    glewExperimental = true;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cout << "glewInit failed: " << glewGetErrorString(err) << std::endl;
        return;
    }

    glViewport(pos.x, pos.y, size.x, size.y);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

//Creating stuff to draw, not really init
void OpenGL::init() {
    //xyz rgb
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

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void OpenGL::draw() {
    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void OpenGL::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

Shader::Shader() {
    vertexShader = compile(GL_VERTEX_SHADER, readFile("../shaders/vertex.glsl"));
    fragmentShader = compile(GL_FRAGMENT_SHADER, readFile("../shaders/fragment.glsl"));
    createProgram();
}

const char* Shader::readFile(const std::string& path) {
    std::string content;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(path);
        content = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        file.close();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << path << std::endl;
    }
    return strcpy(new char[content.length() + 1], content.c_str());
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

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}