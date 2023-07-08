#include "gl.hpp"
#include "mesh.hpp"

enum DrawMode {
    ArrayBuffer = GL_ARRAY_BUFFER,
    ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER
};

enum DrawUsage {
    Dynamic = GL_DYNAMIC_DRAW,
    Static = GL_STATIC_DRAW
};

static void bind_object(DrawMode mode, unsigned int *buffer, unsigned int *object, unsigned int size, DrawUsage usage) {
    CHECK_GL_ERROR(glCreateBuffers(1, buffer));
    CHECK_GL_ERROR(glBindBuffer(mode, *buffer));
    CHECK_GL_ERROR(glBufferData(mode, size, object, usage));
}

static void vertex_attrib_pointer(unsigned int index, unsigned int size, unsigned int stride, unsigned int offset) {
    CHECK_GL_ERROR(glEnableVertexAttribArray(index));
    CHECK_GL_ERROR(glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void*>(offset)));
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) : vertexData(vertices), indexData(indices) {
    CHECK_GL_ERROR(glCreateVertexArrays(1, &inputLayoutObject));
    CHECK_GL_ERROR(glBindVertexArray(inputLayoutObject));

    bind_object(DrawMode::ArrayBuffer, &vertexBufferObject, nullptr, getVertexDataSize(), DrawUsage::Dynamic);
    bind_object(DrawMode::ElementArrayBuffer, &indexBufferObject, indices.data(), indices.size() * sizeof(unsigned int), DrawUsage::Static);

    vertex_attrib_pointer(0, 3, sizeof(Vertex), offsetof(Vertex, position));
    vertex_attrib_pointer(1, 4, sizeof(Vertex), offsetof(Vertex, color));
    vertex_attrib_pointer(2, 2, sizeof(Vertex), offsetof(Vertex, texCoords));
    vertex_attrib_pointer(3, 1, sizeof(Vertex), offsetof(Vertex, textureId));

    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

unsigned int Mesh::getVertexDataSize() const {
    return static_cast<unsigned int>(vertexData.size() * sizeof(Vertex));
}

unsigned int Mesh::getIndexCount() const {
    return static_cast<unsigned int>(indexData.size() * 6);
}

void Mesh::bind(std::vector<Vertex> &vertices) {
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject));
    CHECK_GL_ERROR(glBufferSubData(GL_ARRAY_BUFFER, 0, getVertexDataSize(), vertices.data()));
}

void Mesh::inputLayoutBind() {
    CHECK_GL_ERROR(glBindVertexArray(inputLayoutObject));
}

void Mesh::inputLayoutUnBind() {
    CHECK_GL_ERROR(glBindVertexArray(0));
}

void Mesh::destroy() {
    CHECK_GL_ERROR(glDeleteVertexArrays(1, &inputLayoutObject));
    CHECK_GL_ERROR(glDeleteBuffers(1, &vertexBufferObject));
    CHECK_GL_ERROR(glDeleteBuffers(1, &indexBufferObject));
    CHECK_GL_ERROR(glDeleteTextures(1, &indexBufferObject));
}
