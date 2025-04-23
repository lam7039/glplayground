#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

struct Vertex {
    glm::vec3 position {0.0f};
    glm::vec4 color {1.0f};
    glm::vec2 texCoords;
};

class Mesh {
public:
    //TODO: somehow use a vertexBufferId intead of passing the entire list
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::string texture);

    void bind(std::vector<Vertex> &vertices);
    void input_layout_bind();
    void input_layout_unbind();
    void destroy();
    
    unsigned int get_index_count() const;
    std::string get_texture();
private:
    std::string texture; 
    std::vector<Vertex> vertex_data;
    std::vector<unsigned int> index_data;

    unsigned int input_layout_object {0};
    unsigned int vertex_buffer_object {0};
    unsigned int element_buffer_object {0};
    
    unsigned int get_vertex_data_size() const;
};
