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

static std::array<Vertex, 4> createQuad(float x, float y, float size, float textureId) {
    // top right
    Vertex v0;
    v0.position = {x + size, y, 0.0f};
    v0.color = {1.0f, 0.0f, 0.0f, 1.0f};
    v0.texCoords = {1.0f, 0.0f};
    v0.textureId = textureId;

    // bottom right
    Vertex v1;
    v1.position = {x + size, y + size, 0.0f};
    v1.color = {0.0f, 1.0f, 0.0f, 1.0f};
    v1.texCoords = {1.0f, 1.0f};
    v1.textureId = textureId;

    // bottom left
    Vertex v2;
    v2.position = {x, y + size, 0.0f};
    v2.color = {0.0f, 0.0f, 1.0f, 1.0f};
    v2.texCoords = {0.0f, 1.0f};
    v2.textureId = textureId;

    // top left 
    Vertex v3;
    v3.position = {x, y, 0.0f};
    v3.color = {1.0f, 1.0f, 1.0f, 1.0f};
    v3.texCoords = {0.0f, 0.0f};
    v3.textureId = textureId;

    return {v0, v1, v2, v3};
}

// static Vertex *createQuad(Vertex *target, float x, float y, float size, float textureId) {
//     // top right
//     target->position = {x + size, y, 0.0f};
//     target->color = {1.0f, 0.0f, 0.0f, 1.0f};
//     target->texCoords = {1.0f, 0.0f};
//     target->textureId = textureId;
//     target++;

//     // bottom right
//     target->position = {x + size, y + size, 0.0f};
//     target->color = {0.0f, 1.0f, 0.0f, 1.0f};
//     target->texCoords = {1.0f, 1.0f};
//     target->textureId = textureId;
//     target++;

//     // bottom left
//     target->position = {x, y + size, 0.0f};
//     target->color = {0.0f, 0.0f, 1.0f, 1.0f};
//     target->texCoords = {0.0f, 1.0f};
//     target->textureId = textureId;
//     target++;

//     // top left 
//     target->position = {x, y, 0.0f};
//     target->color = {1.0f, 1.0f, 1.0f, 1.0f};
//     target->texCoords = {0.0f, 0.0f};
//     target->textureId = textureId;
//     target++;

//     indexCount += 6;
//     return target;
// }

static void bind_object(DrawMode mode, unsigned int *buffer, unsigned int *object, unsigned int size, DrawUsage usage) {
    CHECK_GL_ERROR(glCreateBuffers(1, buffer));
    CHECK_GL_ERROR(glBindBuffer(mode, *buffer));
    CHECK_GL_ERROR(glBufferData(mode, size, object, usage));
}

static void vertex_attrib_pointer(unsigned int index, unsigned int size, unsigned int stride, unsigned int offset) {
    CHECK_GL_ERROR(glEnableVertexAttribArray(index));
    CHECK_GL_ERROR(glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void*>(offset)));
}

void VertexArray::init() {
    const size_t maxQuadCount = 8;
    const size_t maxVertexCount = maxQuadCount * 4;
    const size_t maxIndexCount = maxQuadCount * 6;

    int result;
    CHECK_GL_ERROR(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &result));
    std::cout << result << std::endl;

    unsigned int indices[maxIndexCount];
    unsigned int offset = 0;
    for (size_t i = 0; i < maxIndexCount; i += 6) {
        indices [i + 0] = 0 + offset;
        indices [i + 1] = 1 + offset;
        indices [i + 2] = 3 + offset;

        indices [i + 3] = 1 + offset;
        indices [i + 4] = 2 + offset;
        indices [i + 5] = 3 + offset;

        offset += 4;
    }

    CHECK_GL_ERROR(glCreateVertexArrays(1, &glVertexArray.vertexArrayObject));
    CHECK_GL_ERROR(glBindVertexArray(glVertexArray.vertexArrayObject));

    bind_object(DrawMode::ArrayBuffer, &glVertexArray.vertexBufferObject, nullptr, maxQuadCount * sizeof(Vertex), DrawUsage::Dynamic);
    bind_object(DrawMode::ElementArrayBuffer, &glVertexArray.elementBufferObject, indices, sizeof(indices), DrawUsage::Static);

    vertex_attrib_pointer(0, 3, sizeof(Vertex), offsetof(Vertex, position));
    vertex_attrib_pointer(1, 4, sizeof(Vertex), offsetof(Vertex, color));
    vertex_attrib_pointer(2, 2, sizeof(Vertex), offsetof(Vertex, texCoords));
    vertex_attrib_pointer(3, 1, sizeof(Vertex), offsetof(Vertex, textureId));

    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexArray::bind() {
    // std::array<Vertex, 1000> vertices;
    // Vertex *buffer = vertices.data();
    // float size = 10.0f;
    // for (int y = 0; y < 5; y++) {
    //     for (int x = 0; x < 5; x++) {
    //         buffer = createQuad(buffer, x * size, y * size, size, (x + y) % 2);
    //         indexCount += 6;
    //     }
    // }

    auto q0 = createQuad(50.0f, 200.0f, 150.0f, 0.0f);
    auto q1 = createQuad(500.0f, 200.0f, 150.0f, 1.0f);

    Vertex vertices[8];
    memcpy(vertices, q0.data(), q0.size() * sizeof(Vertex));
    memcpy(vertices + q0.size(), q1.data(), q1.size() * sizeof(Vertex));

    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, glVertexArray.vertexBufferObject));
    CHECK_GL_ERROR(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
}

void VertexArray::draw() {
    CHECK_GL_ERROR(glBindVertexArray(glVertexArray.vertexArrayObject));
    CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr));
    CHECK_GL_ERROR(glBindVertexArray(0));
}

void VertexArray::quit() {
    CHECK_GL_ERROR(glDeleteVertexArrays(1, &glVertexArray.vertexArrayObject));
    CHECK_GL_ERROR(glDeleteBuffers(1, &glVertexArray.vertexBufferObject));
    CHECK_GL_ERROR(glDeleteBuffers(1, &glVertexArray.elementBufferObject));
    CHECK_GL_ERROR(glDeleteTextures(1, &glVertexArray.elementBufferObject));
}