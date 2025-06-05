#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 tex_coords;
};

struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};

namespace MeshFactory {
    MeshData generate_cube(float size);
    MeshData generate_rectangle(float width, float height);
    MeshData generate_sphere(float radius, int segments);
}

class Mesh {
public:
    //TODO: somehow use a vertex_buffer_id intead of passing the entire list
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    void bind() const;
    void bind(const std::vector<Vertex>& vertices);
    void input_layout_bind() const;
    void input_layout_unbind() const;
    void destroy();
    
    const unsigned int get_index_count() const;
    const std::string& get_texture() const;
private:
    std::vector<Vertex> vertex_data;
    std::vector<unsigned int> index_data;

    unsigned int vertex_array_object {0};
    unsigned int vertex_buffer_object {0};
    unsigned int index_buffer_object {0};
    
    const unsigned int get_vertex_data_size() const;
};

namespace mesh_utils {
    std::vector<Vertex> generate_vertices(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color = {1.0f, 0.0f, 0.0f, 1.0f});
    std::vector<uint32_t> generate_indices(unsigned int count_vertices);
}
