#include "rectangle.hpp"

static std::vector<Vertex> generate_vertices(const glm::vec3& position, const glm::vec3& size) {
    std::vector<Vertex> vertices(4);
    vertices.push_back({
        position,
        glm::uvec4 {255},
        glm::vec2 {0.0f, 0.0f}
    });
    vertices.push_back({
        glm::vec3 {position.x + size.x, position.y, 0.0f},
        glm::uvec4 {255},
        glm::vec2 {1.0f, 0.0f}
    });
    vertices.push_back({
        position + size,
        glm::uvec4 {255},
        glm::vec2 {1.0f, 1.0f}
    });
    vertices.push_back({
        glm::vec3 {position.x, position.y + size.y, 0.0f},
        glm::uvec4 {255},
        glm::vec2 {0.0f, 1.0f}
    });
    return vertices;
}

static std::vector<unsigned int> generate_indices() {
    std::vector<unsigned int> indices(24);
    unsigned int offset = 0;
    for (unsigned int i = 0; i < 24; i += 6) {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;

        indices[i + 3] = 3 + offset;
        indices[i + 4] = 2 + offset;
        indices[i + 5] = 0 + offset;

        offset += 4;
    }
    return indices;
}

Rectangle::Rectangle(const std::string& texture) {
    vertices = generate_vertices({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f});
    mesh = std::make_shared<Mesh>(vertices, generate_indices(), texture);
}

Rectangle::Rectangle(const glm::vec3& position, const glm::vec3& size, const std::string& texture) {
    vertices = generate_vertices(position, size);
    mesh = std::make_shared<Mesh>(vertices, generate_indices(), texture);
}

void Rectangle::transform(const glm::vec3& position, const glm::vec3& size) {
    vertices[0].position = {position.x, position.y, 0.0f};
    vertices[1].position = {position.x + size.x, position.y, 0.0f};
    vertices[2].position = {position.x + size.x, position.y + size.y, 0.0f};
    vertices[3].position = {position.x, position.y + size.y, 0.0f};
    mesh->bind(vertices);
    vertices.clear();
}

void Rectangle::destroy() {
    vertices.clear();
    mesh->destroy();
    mesh.reset();
}

const std::shared_ptr<Mesh>& Rectangle::get_mesh() const {
    return mesh;
}
