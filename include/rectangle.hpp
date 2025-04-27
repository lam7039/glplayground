#pragma once

#include "mesh.hpp"
#include <memory>

//TODO: create Sprite class to make distinction from Rectangle?
class Rectangle {
public:
    Rectangle(const std::string& texture);
    Rectangle(glm::vec3& position, glm::vec3& size, const std::string& texture);
    // ~Rectangle();

    void transform(glm::vec3& position, glm::vec3& size);
    void destroy();

    const std::shared_ptr<Mesh>& get_mesh() const;
private:
    unsigned int vertex_buffer_index {0};
    std::vector<Vertex> vertices;
    std::shared_ptr<Mesh> mesh;

    void generate_vertices(glm::vec3 position, glm::vec3 size);
    std::vector<unsigned int> generate_indices();
};
