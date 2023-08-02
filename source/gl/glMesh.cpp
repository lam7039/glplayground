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

static void bind_object(DrawMode mode, unsigned int *buffer, unsigned int size, unsigned int *object, DrawUsage usage) {
    CHECK_GL_ERROR(glCreateBuffers(1, buffer));
    CHECK_GL_ERROR(glBindBuffer(mode, *buffer));
    CHECK_GL_ERROR(glBufferData(mode, size, object, usage));
}

static void vertex_attrib_pointer(unsigned int index, unsigned int size, unsigned int stride, unsigned int offset) {
    CHECK_GL_ERROR(glEnableVertexAttribArray(index));
    CHECK_GL_ERROR(glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void*>(offset)));
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, const std::string &texture) : vertexData(vertices), indexData(indices), texture(texture) {
    CHECK_GL_ERROR(glCreateVertexArrays(1, &inputLayoutObject));
    inputLayoutBind();

    bind_object(DrawMode::ArrayBuffer, &vertexBufferObject, getVertexDataSize(), nullptr, DrawUsage::Dynamic);
    bind_object(DrawMode::ElementArrayBuffer, &elementBufferObject, indices.size() * sizeof(unsigned int), indices.data(), DrawUsage::Static);

    vertex_attrib_pointer(0, 3, sizeof(Vertex), offsetof(Vertex, position));
    vertex_attrib_pointer(1, 4, sizeof(Vertex), offsetof(Vertex, color));
    vertex_attrib_pointer(2, 2, sizeof(Vertex), offsetof(Vertex, texCoords));

    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));
    inputLayoutUnbind();
}

unsigned int Mesh::getVertexDataSize() const {
    return static_cast<unsigned int>(vertexData.size() * sizeof(Vertex));
}

unsigned int Mesh::getIndexCount() const {
    return static_cast<unsigned int>(indexData.size() * 6);
}

const std::string &Mesh::getTexture() const {
    return texture;
}

void Mesh::bind(std::vector<Vertex> &vertices) {
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject));
    CHECK_GL_ERROR(glBufferSubData(GL_ARRAY_BUFFER, 0, getVertexDataSize(), vertices.data()));
}

void Mesh::inputLayoutBind() {
    CHECK_GL_ERROR(glBindVertexArray(inputLayoutObject));
}

void Mesh::inputLayoutUnbind() {
    CHECK_GL_ERROR(glBindVertexArray(0));
}

void Mesh::destroy() {
    CHECK_GL_ERROR(glDeleteVertexArrays(1, &inputLayoutObject));
    CHECK_GL_ERROR(glDeleteBuffers(1, &vertexBufferObject));
    CHECK_GL_ERROR(glDeleteBuffers(1, &elementBufferObject));
    CHECK_GL_ERROR(glDeleteTextures(1, &elementBufferObject));
}
