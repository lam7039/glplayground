#pragma once

// #include <assert.h>
// assert(glGetError() == GL_NO_ERROR);

#include <string>
#include <glad/gl.h>

#include "vector2.hpp"
#include "vector3.hpp"

struct GLContext {
    vector2i position;
    vector2i size;
    vector3f color;
};

struct GLShader {
    unsigned int programId {0};
    unsigned int vertexShader {0};
    unsigned int fragmentShader {0};
};

struct GLTexture {
    unsigned int id {0};
    vector2i size;
};

struct GLVertexArray {
    unsigned int vertexArrayObject {0};
    unsigned int vertexBufferObject {0};
    unsigned int elementBufferObject {0};
};
