#include "gl.hpp"
#include "vertex.hpp"
#include <array>
#include <string.h>

// static const unsigned int maxTextures = 32;

// struct GLRenderData {
//     unsigned int quadVertexArray {0};
//     unsigned int quadVertexBuffer {0};
//     unsigned int quadVertexIndexBuffer {0};

//     unsigned int indexCount {0};

//     Vertex *quadBuffer {nullptr};
//     Vertex *quadBufferPtr {nullptr};

//     std::array<unsigned int, maxTextures> textureSlots;
//     unsigned int textureSlotIndex {1};

    
// };

enum DrawMode {
    ArrayBuffer = GL_ARRAY_BUFFER,
    ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER
};

enum DrawUsage {
    Dynamic = GL_DYNAMIC_DRAW,
    Static = GL_STATIC_DRAW
};

static GLVertexArray glVertexArray;

static std::vector<unsigned int> generateIndices(int indexCount) {
    std::vector<unsigned int> indices(indexCount);
    unsigned int offset = 0;
    for (unsigned int i = 0; i < indexCount; i += 6) {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 3 + offset;

        indices[i + 3] = 1 + offset;
        indices[i + 4] = 2 + offset;
        indices[i + 5] = 3 + offset;

        offset += 4;
    }
    return indices;
}

static void bind_object(DrawMode mode, unsigned int *buffer, unsigned int *object, unsigned int size, DrawUsage usage) {
    CHECK_GL_ERROR(glCreateBuffers(1, buffer));
    CHECK_GL_ERROR(glBindBuffer(mode, *buffer));
    CHECK_GL_ERROR(glBufferData(mode, size, object, usage));
}

static void vertex_attrib_pointer(unsigned int index, unsigned int size, unsigned int stride, unsigned int offset) {
    CHECK_GL_ERROR(glEnableVertexAttribArray(index));
    CHECK_GL_ERROR(glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void*>(offset)));
}

void VertexArray::init(std::vector<Vertex> &vertices) {
    const int maxQuadCount = 8;
    const int maxVertexCount = maxQuadCount * 4;
    const int maxIndexCount = maxQuadCount * 6;

    int result;
    CHECK_GL_ERROR(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &result));
    std::cout << result << std::endl;

    CHECK_GL_ERROR(glCreateVertexArrays(1, &glVertexArray.vertexArrayObject));
    CHECK_GL_ERROR(glBindVertexArray(glVertexArray.vertexArrayObject));

    std::vector<unsigned int> indices = generateIndices(maxIndexCount);
    bind_object(DrawMode::ArrayBuffer, &glVertexArray.vertexBufferObject, nullptr, vertices.size() * sizeof(Vertex), DrawUsage::Dynamic);
    bind_object(DrawMode::ElementArrayBuffer, &glVertexArray.elementBufferObject, indices.data(), indices.size() * sizeof(unsigned int), DrawUsage::Static);

    vertex_attrib_pointer(0, 3, sizeof(Vertex), offsetof(Vertex, position));
    vertex_attrib_pointer(1, 4, sizeof(Vertex), offsetof(Vertex, color));
    vertex_attrib_pointer(2, 2, sizeof(Vertex), offsetof(Vertex, texCoords));
    vertex_attrib_pointer(3, 1, sizeof(Vertex), offsetof(Vertex, textureId));

    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexArray::bind(std::vector<Vertex> &vertices) {
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, glVertexArray.vertexBufferObject));
    CHECK_GL_ERROR(glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data()));
}

void VertexArray::draw() {
    CHECK_GL_ERROR(glBindVertexArray(glVertexArray.vertexArrayObject));
    CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr));
    CHECK_GL_ERROR(glBindVertexArray(0));
}

void VertexArray::clear() {
    CHECK_GL_ERROR(glDeleteVertexArrays(1, &glVertexArray.vertexArrayObject));
    CHECK_GL_ERROR(glDeleteBuffers(1, &glVertexArray.vertexBufferObject));
    CHECK_GL_ERROR(glDeleteBuffers(1, &glVertexArray.elementBufferObject));
    CHECK_GL_ERROR(glDeleteTextures(1, &glVertexArray.elementBufferObject));
}
