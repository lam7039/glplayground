#pragma once

// #include "mesh.hpp"
// #include <memory>

// //TODO: create Sprite class to make distinction from Rectangle?
// class Rectangle {
// public:
//     Rectangle(const std::string& texture);
//     Rectangle(const glm::vec3& position, const glm::vec3& size, const std::string& texture, const glm::vec4& color);

//     void transform(const glm::vec3& position, const glm::vec3& size);
//     void destroy();

//     const std::shared_ptr<Mesh>& get_mesh() const;
// private:
//     unsigned int vertex_buffer_index {0};
//     std::vector<Vertex> vertices;
//     std::shared_ptr<Mesh> mesh;
// };

// //Rectangle as a geometric concept only (position, size, rotation, tranforms)

#include <glm/glm.hpp>

class Rectangle {
public:
    Rectangle(glm::vec3 position, glm::vec3 size);
    const glm::vec3 get_position() const;
    const glm::vec3 get_size() const;

    void transform(glm::vec3 position, glm::vec3 size);
private:
    glm::vec3 position;
    glm::vec3 size;
};
