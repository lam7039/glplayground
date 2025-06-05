#include "rectangle.hpp"

// #include <iostream>

// static std::vector<Vertex> generate_vertices(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color = {1.0f, 0.0f, 0.0f, 1.0f}) {
//     return {
//         {
//             position,
//             color,
//             glm::vec2 {0.0f, 0.0f}
//         },
//         {
//             glm::vec3 {position.x + size.x, position.y, 0.0f},
//             color,
//             glm::vec2 {1.0f, 0.0f}
//         },
//         {
//             position + size,
//             color,
//             glm::vec2 {1.0f, 1.0f}
//         },
//         {
//             glm::vec3 {position.x, position.y + size.y, 0.0f},
//             color,
//             glm::vec2 {0.0f, 1.0f}
//         }
//     };
// }

// static std::vector<uint32_t> generate_indices(unsigned int count_vertices) {
//     int count_quads = 1;
//     int count_indices = 6;
//     std::vector<uint32_t> indices(count_quads * count_indices);
//     unsigned int offset = 0;
//     for (unsigned int i = 0; i < count_quads * count_indices; i += count_indices) {
//         indices[i + 0] = 0 + offset;
//         indices[i + 1] = 1 + offset;
//         indices[i + 2] = 2 + offset;

//         indices[i + 3] = 3 + offset;
//         indices[i + 4] = 2 + offset;
//         indices[i + 5] = 0 + offset;

//         offset += count_vertices;
//     }
//     return indices;
// }

// Rectangle::Rectangle(const std::string& texture) {
//     vertices = generate_vertices({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f});
//     mesh = std::make_shared<Mesh>(vertices, generate_indices(vertices.size()));
// }

// Rectangle::Rectangle(const glm::vec3& position, const glm::vec3& size, const std::string& texture, const glm::vec4& color) {
//     vertices = generate_vertices(position, size, color);
//     mesh = std::make_shared<Mesh>(vertices, generate_indices(vertices.size()));
// }

// void Rectangle::transform(const glm::vec3& position, const glm::vec3& size) {
//     // vertices[0].position = {position.x, position.y, 0.0f};
//     // vertices[1].position = {position.x + size.x, position.y, 0.0f};
//     // vertices[2].position = {position.x + size.x, position.y + size.y, 0.0f};
//     // vertices[3].position = {position.x, position.y + size.y, 0.0f};
//     // mesh->bind(vertices);
//     // vertices.clear();
//     // std::cout <<"clear" << std::endl;
// }

// void Rectangle::destroy() {
//     vertices.clear();
//     mesh->destroy();
//     mesh.reset();
// }

// const std::shared_ptr<Mesh>& Rectangle::get_mesh() const {
//     return mesh;
// }

Rectangle::Rectangle(glm::vec3 position, glm::vec3 size) {
    this->position = position;
    this->size = size;
}

const glm::vec3 Rectangle::get_position() const {
    return position;
}

const glm::vec3 Rectangle::get_size() const {
    return size;
}

void Rectangle::transform(glm::vec3 position, glm::vec3 size) {
    this->position = position;
    this->size = size;
}
