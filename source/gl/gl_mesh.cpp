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

enum DataType {
    Float = GL_FLOAT,
    UnsignedInt = GL_UNSIGNED_INT
};

static void bind_object(DrawMode mode, unsigned int* object, unsigned int size, unsigned int* data, DrawUsage usage) {
    CHECK_GL_ERROR(glGenBuffers(1, object));
    CHECK_GL_ERROR(glBindBuffer(mode, *object));
    CHECK_GL_ERROR(glBufferData(mode, size, data, usage));
}

static void vertex_attrib_pointer(unsigned int index, unsigned int size, unsigned int stride, unsigned int offset, DataType type = DataType::Float, bool normalized = GL_FALSE) {
    CHECK_GL_ERROR(glEnableVertexAttribArray(index));
    CHECK_GL_ERROR(glVertexAttribPointer(index, size, type, normalized, stride, reinterpret_cast<const void*>(offset)));
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) : vertex_data(vertices), index_data(indices) {
    CHECK_GL_ERROR(glGenVertexArrays(1, &vertex_array_object));
    input_layout_bind();

    bind_object(DrawMode::ArrayBuffer, &vertex_buffer_object, get_vertex_data_size(), nullptr, DrawUsage::Dynamic);
    bind_object(DrawMode::ElementArrayBuffer, &index_buffer_object, indices.size() * sizeof(unsigned int), indices.data(), DrawUsage::Static);

    vertex_attrib_pointer(0, 3, sizeof(Vertex), offsetof(Vertex, position));
    vertex_attrib_pointer(1, 4, sizeof(Vertex), offsetof(Vertex, color));
    vertex_attrib_pointer(2, 2, sizeof(Vertex), offsetof(Vertex, tex_coords));

    CHECK_GL_ERROR(glBindBuffer(DrawMode::ArrayBuffer, 0));
    input_layout_unbind();
}

const unsigned int Mesh::get_vertex_data_size() const {
    return static_cast<unsigned int>(vertex_data.size() * sizeof(Vertex));
}

const unsigned int Mesh::get_index_count() const {
    return static_cast<unsigned int>(index_data.size());
}

//TODO: rename to update_buffers, only call if data actually changes
void Mesh::bind() const {
    CHECK_GL_ERROR(glBindBuffer(DrawMode::ArrayBuffer, vertex_buffer_object));
    CHECK_GL_ERROR(glBindBuffer(DrawMode::ElementArrayBuffer, index_buffer_object));
    CHECK_GL_ERROR(glBufferSubData(DrawMode::ArrayBuffer, 0, get_vertex_data_size(), vertex_data.data()));
}

//TODO: use shared_ptr for vertices so we don't have to constantly pass vertices to bind?
void Mesh::bind(const std::vector<Vertex>& vertices) {
    vertex_data = vertices;
    bind();
}

void Mesh::input_layout_bind() const {
    CHECK_GL_ERROR(glBindVertexArray(vertex_array_object));
}

void Mesh::input_layout_unbind() const {
    CHECK_GL_ERROR(glBindVertexArray(0));
}

void Mesh::destroy() {
    CHECK_GL_ERROR(glDeleteVertexArrays(1, &vertex_array_object));
    CHECK_GL_ERROR(glDeleteBuffers(1, &vertex_buffer_object));
    CHECK_GL_ERROR(glDeleteBuffers(1, &index_buffer_object));
    CHECK_GL_ERROR(glDeleteTextures(1, &index_buffer_object)); //TODO: why deleteTextures here? probably a good reason but can't remember atm
    index_data.clear();
    vertex_data.clear();
}

namespace mesh_utils {
    std::vector<Vertex> generate_vertices(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color) {
        return {
            {
                position,
                color,
                glm::vec2 {0.0f, 0.0f}
            },
            {
                glm::vec3 {position.x + size.x, position.y, 0.0f},
                color,
                glm::vec2 {1.0f, 0.0f}
            },
            {
                position + size,
                color,
                glm::vec2 {1.0f, 1.0f}
            },
            {
                glm::vec3 {position.x, position.y + size.y, 0.0f},
                color,
                glm::vec2 {0.0f, 1.0f}
            }
        };
    }

    std::vector<uint32_t> generate_indices(unsigned int count_vertices) {
        int count_quads = 1;
        int count_indices = 6;
        std::vector<uint32_t> indices(count_quads * count_indices);
        unsigned int offset = 0;
        for (unsigned int i = 0; i < count_quads * count_indices; i += count_indices) {
            indices[i + 0] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;

            indices[i + 3] = 3 + offset;
            indices[i + 4] = 2 + offset;
            indices[i + 5] = 0 + offset;

            offset += count_vertices;
        }
        return indices;
    }
}
