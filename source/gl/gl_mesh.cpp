#include "gl/gl.hpp"
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

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::string texture) : vertex_data(vertices), index_data(indices), texture(texture) {
    CHECK_GL_ERROR(glCreateVertexArrays(1, &input_layout_object));
    input_layout_bind();

    bind_object(DrawMode::ArrayBuffer, &vertex_buffer_object, get_vertex_data_size(), nullptr, DrawUsage::Dynamic);
    bind_object(DrawMode::ElementArrayBuffer, &element_buffer_object, indices.size() * sizeof(unsigned int), indices.data(), DrawUsage::Static);

    vertex_attrib_pointer(0, 3, sizeof(Vertex), offsetof(Vertex, position));
    vertex_attrib_pointer(1, 4, sizeof(Vertex), offsetof(Vertex, color));
    vertex_attrib_pointer(2, 2, sizeof(Vertex), offsetof(Vertex, texCoords));

    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));
    input_layout_unbind();
}

unsigned int Mesh::get_vertex_data_size() const {
    return static_cast<unsigned int>(vertex_data.size() * sizeof(Vertex));
}

unsigned int Mesh::get_index_count() const {
    return static_cast<unsigned int>(index_data.size() * 6);
}

std::string Mesh::get_texture() {
    return texture;
}

void Mesh::bind(std::vector<Vertex> &vertices) {
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object));
    CHECK_GL_ERROR(glBufferSubData(GL_ARRAY_BUFFER, 0, get_vertex_data_size(), vertices.data()));
}

void Mesh::input_layout_bind() {
    CHECK_GL_ERROR(glBindVertexArray(input_layout_object));
}

void Mesh::input_layout_unbind() {
    CHECK_GL_ERROR(glBindVertexArray(0));
}

void Mesh::destroy() {
    CHECK_GL_ERROR(glDeleteVertexArrays(1, &input_layout_object));
    CHECK_GL_ERROR(glDeleteBuffers(1, &vertex_buffer_object));
    CHECK_GL_ERROR(glDeleteBuffers(1, &element_buffer_object));
    CHECK_GL_ERROR(glDeleteTextures(1, &element_buffer_object));
}
