#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

struct Vertex {
    glm::vec3 position {0.0f};
    glm::uvec4 color {255};
    glm::vec2 tex_coords;
};

class Mesh {
public:
    //TODO: somehow use a vertex_buffer_id intead of passing the entire list
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::string texture);

    void bind() const;
    void bind(std::vector<Vertex>& vertices) const;
    void input_layout_bind() const;
    void input_layout_unbind() const;
    void destroy() const;
    
    const unsigned int get_index_count() const;
    const std::string& get_texture() const;
private:
    std::string texture; 
    std::vector<Vertex> vertex_data;
    std::vector<unsigned int> index_data;

    unsigned int vertex_array_object {0};
    unsigned int vertex_buffer_object {0};
    unsigned int index_buffer_object {0};
    
    const unsigned int get_vertex_data_size() const;
};
